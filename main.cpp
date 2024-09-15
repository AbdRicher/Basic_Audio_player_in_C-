#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <mmsystem.h>  // Required for PlaySound

#pragma comment(lib,"winmm.lib")
using namespace std;

class AudioPlayer {
protected:
    const char* filePath;
public:
    AudioPlayer(const char* filePath) : filePath(filePath) {}

    void playSound() {
        char command[256];
        sprintf(command, "open \"%s\" type mpegvideo alias mySound", filePath);
        mciSendString(command, NULL, 0, NULL);
        mciSendString("play mySound", NULL, 0, NULL);
    }

    void stopSound() {
        mciSendString("stop mySound", NULL, 0, NULL);
        mciSendString("close mySound", NULL, 0, NULL);
    }

    void pauseSound() {
        mciSendString("pause mySound", NULL, 0, NULL);
    }

    void resumeSound() {
        mciSendString("resume mySound", NULL, 0, NULL);
    }
};

class Playlist {
private:
    vector<pair<string, string>> songs; // Pair of song name and file path
public:
    void addSong(const string& name, const string& path) {
        songs.push_back(make_pair(name, path));
    }

    void displaySongs() const {
        for (size_t i = 0; i < songs.size(); ++i) {
            cout << i + 1 << ". " << songs[i].first << endl;
        }
    }

    const char* getSongPath(int index) const {
        if (index >= 0 && index < songs.size()) {
            return songs[index].second.c_str();
        }
        return nullptr;
    }
};

class InteractiveAudioPlayer : public AudioPlayer {
private:
    Playlist playlist;
public:
    InteractiveAudioPlayer(const char* filePath) : AudioPlayer(filePath) {}

    void addSongsToPlaylist() {
        // Add songs to the path
        playlist.addSong("Song 1", "C:\\Users\\AS's PC\\Desktop\\New folder\\Audioplayer\\audio\\song1.wav");
        playlist.addSong("Song 2", "C:\\Users\\AS's PC\\Desktop\\New folder\\Audioplayer\\audio\\song2.wav");
        playlist.addSong("Song 3", "C:\\Users\\AS's PC\\Desktop\\New folder\\Audioplayer\\audio\\song3.wav");
        playlist.addSong("Song 4", "C:\\Users\\AS's PC\\Desktop\\New folder\\Audioplayer\\audio\\song4.wav");
    }

    void run() {
        addSongsToPlaylist();
        int choice;
        while (true) {
            playlist.displaySongs();
            cout << "Select a song to play: ";
            int songChoice;
            cin >> songChoice;
            const char* selectedSongPath = playlist.getSongPath(songChoice - 1);
            if (selectedSongPath) {
                filePath = selectedSongPath;
                playSound();
                cout << "Playing " << filePath << endl;
            } else {
                cout << "Invalid choice. Please try again." << endl;
                continue;
            }

            while (true) {
                    system("cls");
                cout << "\n--------------------Controls-------------------------\n" << endl;
                cout << "For pause press 1\nFor resume press 2\nFor stop press 3\nFor exit Program press 4\n";
                cout << "\n-----------------------------------------------------\n" << endl;
                cout << "Your choice: ";
                cin >> choice;
                system("cls");
                switch (choice) {
                    case 1:
                        pauseSound();
                        cout << "Paused " << filePath << endl;
                        break;
                    case 2:
                        resumeSound();
                        cout << "Resumed " << filePath << endl;
                        break;
                    case 3:
                        stopSound();
                        cout << "Stopped " << filePath << endl;
                        break;
                    case 4:
                        stopSound(); // Ensure the sound is stopped before exiting
                        cout << "Exiting..." << endl;
                        return;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                }
                if (choice == 3) {
                    break; // Break out of the inner loop to select a new song
                }
                if (choice == 4) {
                    return; // Exit the program
                }
            }
        }
    }
};

int main() {
    // Add your Path
    const char* filePath = "C:\\Users\\AS's PC\\Desktop\\New folder\\Audioplayer\\audio\\bhagwan.wav";
    InteractiveAudioPlayer player(filePath);
    player.run();
    return 0;
}
