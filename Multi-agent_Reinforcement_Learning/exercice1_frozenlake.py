import gym
import numpy as np
import random


class Agent:
    def __init__(self, action_space, q_table_shape, alpha, gamma, epsilon):
        self.action_space = action_space
        self.q_table = np.zeros(shape=q_table_shape)
        self.alpha = alpha
        self.gamma = gamma
        self.epsilon = epsilon

    def act(self, state):
        # Select action for exploitation or exploitation
        # YOUR CODE HERE
        # The greater Epsilon (in the first expisodes), the more chances
        # there are of a randomly selected action
        # Otherwise (last expisodes) take the best action from the q_table
        if np.random.uniform(0, 1) < self.epsilon:
            action = env.action_space.sample()
        else:
            action = np.argmax(self.q_table[state, :])
        return action

    def learn(self, state, action, reward, next_state):
        # Update Q table based on experience
        # YOUR CODE HERE
        # Implementation of the Q-learning formula
        self.q_table[state, action] = self.q_table[state, action] + \
            self.alpha * (reward + self.gamma * np.max(
                self.q_table[next_state, :])
            - self.q_table[state, action])


env = gym.make('FrozenLake-v0')

alpha = 0.9  # YOUR CODE HERE
gamma = 0.9  # YOUR CODE HERE
epsilon = 0.9  # YOUR CODE HERE

my_agent = Agent(env.action_space, (env.observation_space.n,
                                    env.action_space.n),
                 alpha, gamma, epsilon)

num_expisodes = 10000
max_steps = 100
total_reward = 0

for i in range(num_expisodes):
    done = False
    t = 0
    ep_reward = 0
    state = env.reset()

    while t < max_steps:
        # YOUR CODE HERE
        action = my_agent.act(state)  # Next action
        next_state, reward, done, info = env.step(action)
        # YOUR CODE HERE
        my_agent.learn(state, action, reward, next_state)  # Updating Q-table
        state = next_state  # Update the state
        t += 1
        ep_reward += reward
        if done:
            break

    # Decrease slowly epsilon every expisodes to regulate the learning
    if(my_agent.epsilon > 0):  # YOUR CODE HERE
        my_agent.epsilon -= 0.001  # YOUR CODE HERE
    total_reward += ep_reward
print("Accumulated reward:", total_reward / num_expisodes)
print("\nBest value:", np.argmax(my_agent.q_table, axis=1))
print("Q-Table values:\n", my_agent.q_table)
