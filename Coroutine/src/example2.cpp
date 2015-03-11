struct World {
    boost::coroutines::asymmetric_coroutine<int>::pull_type coro;
    int do_events() {
        coro();
        if (coro) {
            return coro.get();
        } else {
            throw EndOfWorld{};
        }
    }
};

struct enemy
{
    bool defend(World world) {
        if (being_attacked()) {
            defend_time = 3;
            while(defend_time > 0) {
                defend_time -= world.do_events();
            }
        }
    }

    void search(World world) {
        optional<Target> t = boost::none;
        do {
            defend();
            t = look_for_target();
            if (!t) {
                world.do_events();
            }
        } while(t)
    }

    void seek(World world) {
        while (!touching(target)) {
            // Has to call world to pass time to move_to
            move_to(target, world.do_events());
            defend();
        }
    }

    void attack(World world) {
        while (play_animation(wind_up)) {
            world.do_events();
        }
        while (play_animation(unleash)) {
            world.do_events();
        }
    }

    void update(asymmetric_coroutine<int> & world) {
        while(true) {
            search(world);
            seek(world);
            attack(world);
        }
    }
};

