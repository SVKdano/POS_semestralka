#include "head/game.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <cstdlib>

Game game;

void renderGame(std::condition_variable * renderAll, std::condition_variable * notify, sf::RenderWindow *window, std::mutex *mutex, bool * updating) {
    while(game.isWindowOpened()) {
        window->setActive(true);
        std::unique_lock<std::mutex> lock(* mutex);

        while (!(*updating)) renderAll->wait(lock);

        game.renderWindow();
        (*updating) = false;
        notify->notify_one();
    }
}

void updateGame(std::condition_variable * renderAll, std::condition_variable * notify, std::mutex *mutex, bool * updating) {
    while(game.isWindowOpened()) {
        std::unique_lock<std::mutex> lock(*mutex);

        while (*updating) notify->wait(lock);

        game.updateWindow();
        (*updating) = true;
        renderAll->notify_one();
    }
}

int main()
{
    std::condition_variable renderAll, notify;
    std::mutex mutex;
    bool updating = false;

    game.getWindow()->setActive(false);
    std::thread thread(renderGame, &renderAll, &notify, game.getWindow(), &mutex, &updating);
    updateGame(&renderAll, &notify, &mutex, &updating);
    thread.join();

    return 0;
}