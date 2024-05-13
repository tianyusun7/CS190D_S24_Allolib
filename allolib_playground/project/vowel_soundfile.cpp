#include <iostream>
#include <vector>
#include "al/app/al_App.hpp"
#include "al/io/al_Imgui.hpp"
#include "al/sound/al_SoundFile.hpp"

using namespace al;

// vowel sound reverse engineering, try to read vowel sound file and visualize and manipulate it

//#define FRAME_SIZE 1000000

struct MyApp : App {
  SoundFilePlayerTS playerTS;
  std::vector<float> buffer;
  bool loop = true;
  Mesh spectrumMesh;
  //float spectrum[FRAME_SIZE];

  void onInit() override {
    const char name[] = "data/five_vowels.wav"; 
    if (!playerTS.open(name)) {
      std::cerr << "File not found: " << name << std::endl;
      quit();
    }
    std::cout << "sampleRate: " << playerTS.soundFile.sampleRate << std::endl;
    std::cout << "channels: " << playerTS.soundFile.channels << std::endl;
    std::cout << "frameCount: " << playerTS.soundFile.frameCount << std::endl;
    /*
    for (auto data:playerTS.soundFile.data) {
      std::cout << data << " " << std::endl;
    }
    */
    
    std::cout << "soundfile data size: " << playerTS.soundFile.data.size() << std::endl; //each frame is one sample data, stored in a vector
    //std::cout << "data: " << playerTS.soundFile.data << std::endl;
    playerTS.setLoop();
    playerTS.setPlay();
  }

  void onCreate() override { imguiInit(); }

  void onSound(AudioIOData& io) override {
    int frames = (int)io.framesPerBuffer();
    int channels = playerTS.soundFile.channels;
    int bufferLength = frames * channels;
    if ((int)buffer.size() < bufferLength) {
      buffer.resize(bufferLength);
    }
    playerTS.getFrames(frames, buffer.data(), (int)buffer.size());
    int second = (channels < 2) ? 0 : 1;
    while (io()) {
      int frame = (int)io.frame();
      int idx = frame * channels;
      io.out(0) = buffer[idx];
      io.out(1) = buffer[idx + second];
    }
  }

  void onAnimate(double dt) override {
    // Create spectrum mesh. You don't want to do this in the audio callback.
    spectrumMesh.reset();
    spectrumMesh.primitive(Mesh::LINE_STRIP);
    for (int i = 0; i < playerTS.soundFile.data.size(); i++) {
      spectrumMesh.color(HSV(0.5 - playerTS.soundFile.data[i] * 100));
      spectrumMesh.vertex(i, playerTS.soundFile.data[i], 0.0);
    }
  }

  void onDraw(Graphics& g) override {
    imguiBeginFrame();
    ImGui::Begin("control window");
    if (ImGui::Button("play")) {
      playerTS.setPlay();
    }
    if (ImGui::Button("pause")) {
      playerTS.setPause();
    }
    if (ImGui::Button("toggle pause")) {
      playerTS.togglePause();
    }
    if (ImGui::Button("rewind")) {
      playerTS.setRewind();
    }
    if (ImGui::Checkbox("loop", &loop)) {
      if (loop) {
        playerTS.setLoop();
      } else {
        playerTS.setNoLoop();
      }
    }
    
    ImGui::End();
    imguiEndFrame();
    g.clear(0, 0, 0);
    imguiDraw();
    /*
    g.meshColor();  // Use the color in the mesh
    g.pushMatrix();
    g.translate(-1.0, 0, -4.0);
    g.scale(4.0 / playerTS.soundFile.data.size(), 100, 1.0);
    g.draw(spectrumMesh);
    g.popMatrix();
    */
    
  }


  void onExit() override { imguiShutdown(); }
};

int main() {
  MyApp app;
  app.configureAudio(44100, 512, 2, 0);
  app.start();
}
