

#include "head/game.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <cstdlib>

sf::Context context;
Game game;

void render(bool * isUpdated, std::mutex *mut, std::condition_variable * render, std::condition_variable * update, sf::RenderWindow *window) {
    while(game.isWindowOpened()) {
        window->setActive(true);
        std::unique_lock<std::mutex> lock(* mut);
        while (!(*isUpdated)) render->wait(lock);
        game.renderWindow();
        (*isUpdated) = false;
        update->notify_one();
    }
}

void update(bool * isUpdated, std::mutex *mut, std::condition_variable * render, std::condition_variable * update) {
    while(game.isWindowOpened()) {
        std::unique_lock<std::mutex> lock(*mut);
        while (*isUpdated) update->wait(lock);
        game.updateWindow();
        (*isUpdated) = true;
        render->notify_one();
    }
}

int main()
{
    std::cout << "som tu" << std::endl;
    putenv("DISPLAY=192.168.0.104:7.0");
    //setenv("DISPLAY","192.168.0.104:7.0",true);
    std::mutex mut;
    std::condition_variable rend, upd;
    bool isUpdated = false;
    game.getWindow()->setActive(false);
    std::thread t1(render,&isUpdated, &mut,&rend, &upd, game.getWindow());
    update(&isUpdated, &mut,&rend, &upd);
    t1.join();
    return 0;
}

