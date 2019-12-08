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
        action = 0
        if np.random.uniform(0, 1) < epsilon:
            action = env.action_space.sample()
        else:
            action = np.argmax(self.q_table[state, action])
        return action

    def learn(self, state, action, reward, next_state):
        # Update Q table based on experience
        # YOUR CODE HERE
        self.q_table[state, action] = self.q_table[state, action] + self.alpha(
            reward + self.epsilon * np.max(self.q_table[next_state, action])
            - self.q_table[state, action])


env = gym.make('FrozenLake-v0')

alpha = 0.1  # YOUR CODE HERE
gamma = 0.99  # YOUR CODE HERE
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

    if(done):  # YOUR CODE HERE
        my_agent.epsilon = 1  # YOUR CODE HERE
        total_reward += ep_reward
        print(total_reward/num_expisodes)
