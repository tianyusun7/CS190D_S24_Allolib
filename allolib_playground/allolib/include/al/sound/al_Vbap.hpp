#ifndef INCLUDE_AL_PANNING_VBAP
#define INCLUDE_AL_PANNING_VBAP

/*	Allocore --
        Multimedia / virtual environment application class library

        Copyright (C) 2009. AlloSphere Research Group, Media Arts & Technology,
   UCSB. Copyright (C) 2012. The Regents of the University of California. All
   rights reserved.

        Redistribution and use in source and binary forms, with or without
        modification, are permitted provided that the following conditions are
   met:

                Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

                Redistributions in binary form must reproduce the above
   copyright notice, this list of conditions and the following disclaimer in the
                documentation and/or other materials provided with the
   distribution.

                Neither the name of the University of California nor the names
   of its contributors may be used to endorse or promote products derived from
                this software without specific prior written permission.

        THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
   IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
        IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
   PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
   OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
   OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
   ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


        File description:
        Vector-based amplitude panner (VBAP)

        File author(s):
        Ryan McGee, 2012, ryanmichaelmcgee@gmail.com
*/

#include <map>

#include "al/math/al_Vec.hpp"
#include "al/sound/al_Spatializer.hpp"
#include "al/sound/al_Speaker.hpp"
#include "al/spatial/al_DistAtten.hpp"
#include "al/spatial/al_Pose.hpp"

#define MAX_NUM_VBAP_TRIPLETS 512
//#define MIN_VOLUME_TO_LENGTH_RATIO 0.01

#define MIN_VOLUME_TO_LENGTH_RATIO 0.000001
#define MIN_LENGTH 0.00001

namespace al {

/// A triplet of speakers
struct SpeakerTriple {
  int s1;
  Vec3d s1Vec;
  int s2;
  Vec3d s2Vec;
  int s3;
  Vec3d s3Vec;
  Vec3d vec[3];
  Mat3d mat;
  int speakerIdx[3];

  // Speaker speakers[3];
  unsigned int speakerChan[3];
  unsigned int s1Chan;
  unsigned int s2Chan;
  unsigned int s3Chan;

  bool loadVectors(const std::vector<Speaker> &spkrs);
};

/// Vector-based amplitude panner
///
/// @ingroup Sound
class Vbap : public Spatializer {
public:
  typedef enum {
    KEEP_SAME_ELEVATION =
        0x1, // Don't discard triplets that have the same elevation
  } VbapOptions;

  /// @param[in] sl	A speaker layout
  Vbap(const Speakers &sl, bool is3D = false);

  void setOptions(VbapOptions options) { mOptions = options; }

  virtual void compile() override;

  ///
  /// \brief Make an existing channel a phantom channel
  /// \param channelIndex the channel index of the phantom channel
  /// \param assignedOutputs the list of channel indeces for signal reassignment
  ///
  /// Signals that should go out to phantom channels will be distributed among
  /// the channels listed in the assignedOutputs vector. This can be useful to
  /// force triangulation in unusual situations (e.g. three rings on a
  /// sphere...) but it can also be used creatively to make an area in space
  /// be reassigned somewhere else, or to a wider number of speakers.
  ///
  void makePhantomChannel(int channelIndex,
                          std::vector<unsigned int> assignedOutputs);

  /// Set whether VBAP will use 3D (triangles) or 2D (speaker pairs)
  /// You must call compile after this function to ensure triples are
  /// recomputed
  void set3D(bool is3D) { mIs3D = is3D; }

  virtual void renderSample(AudioIOData &io, const Vec3f &reldir,
                            const float &sample,
                            const unsigned int &frameIndex) override;
  virtual void renderBuffer(AudioIOData &io, const Vec3f &pos,
                            const float *samples,
                            const unsigned int &numFrames) override;

  virtual void print(std::ostream &stream = std::cout) override;

  /// Manually add a triple from indeces to speakers
  void makeTriple(int s1, int s2, int s3 = -1);

  // Returns vector of triplets
  std::vector<SpeakerTriple> triplets() const;

private:
  std::vector<SpeakerTriple> mTriplets;
  std::map<unsigned int, std::vector<unsigned int>> mPhantomChannels;
  //	Listener* mListener;
  bool mIs3D;
  VbapOptions mOptions;

  Vec3d computeGains(const Vec3d &vecA, const SpeakerTriple &speak);

  /// 2D VBAP, Build internal list of speaker pairs
  void findSpeakerPairs(const Speakers &spkrs);

  /// 3D VBAP, build list of internal speaker triplets
  void findSpeakerTriplets(const Speakers &spkrs);

  bool isCrossing(Vec3d c, Vec3d li, Vec3d lj, Vec3d ln, Vec3d lm);

  /// Manually add triplet of speakers, in case not set automatically
  void addTriple(const SpeakerTriple &st);
};

} // namespace al
#endif
