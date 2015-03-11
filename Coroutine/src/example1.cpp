struct enemy
{
    enum state {
        seeking = 1,
        attacking = 2,
        defending = 3
    };
    int attack_phase;
    coord target;
    state current_state;
    int defend_time;
    Target target;

    void update(int elapsed_time) {
        switch(current_state) {
            case searching:
                optional<Target> t = look_for_target();
                if (t) {
                    current_state == seeking;
                    target = t.get();
                }
                if (being_attacked()) {
                    current_state = defending;
                    defend_time = 3;
                }
            case seeking:
                move_to(target, elapsed_time);
                if (being_attacked()) {
                    current_state = defending;
                    defend_time = 0;
                }
                if (touching(target)) {
                    current_state = attacking;
                    attack_phase = 0;
                }
                break;
            case attacking:
                switch (attack_phase) {
                    case 0:
                        if (play_animation(wind_up))
                        {
                            ++ attack_phase;
                        }
                        break;
                    case 1:
                        if (play_animation(unleash))
                        {
                            current_state = seeking;
                        }
                        break;
                    default:
                        break;
                }
                break;
            case defending:
                defend_time -= elapsed_time;
                if (defend_time <= 0) {
                    current_state = seeking;
                }
                break;
            default:
                break;
        }
    }
};

