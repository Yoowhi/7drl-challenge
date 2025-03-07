#include "ActionQueue.hpp"

ActionQueue::ActionQueue() {}

ActionQueue::~ActionQueue() {
    actions.clearAndDelete();
}

/**
 * @short Keeps order from biggest value of action->priority to lowest
 */
void ActionQueue::add(Action* action) {
    int i = 0;
    bool found = false;
    for (Action** iter = actions.begin(); iter != actions.end(); iter++) {
        Action* queueElement = *iter;
        if (action->time >= queueElement->timeLeft) {
            found = true;
            break;
        }
        i++;
    }
    if (found) {
        actions.insertBefore(action, i);
    } else {
        actions.push(action);
    }
}

void ActionQueue::clearFromActor(Entity* actor) {
    for (Action** iter = actions.begin(); iter < actions.end(); iter++) {
        Action* action = *iter;
        if (action->actor == actor) {
            actions.remove(iter);
            break;
        }
    }

}

Action* ActionQueue::next() {
    if (actions.size() == 0) {
        return NULL;
    }
    Action* action = actions.pop();
    for (Action** iter = actions.begin(); iter < actions.end(); iter++) {
        Action* queueElement = *iter;
        queueElement->timeLeft -= action->time;
    }
    return action;
}
