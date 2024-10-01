//Question
// Design and implement a basic version of Twitter.

// Implement the following functionalities:

// Post a tweet: Users should be able to post a tweet with a unique tweet ID and tweet text. The system should automatically timestamp each tweet.
// Get news feed: Retrieve the 10 most recent tweets from a user’s news feed. The news feed should consist of tweets from the user themself as well as from the users they follow. The tweets should be ordered from the most recent to the least recent.
// Follow a user: A user should be able to follow another user. Once a user follows someone, they should be able to see that person's tweets in their news feed.
// Unfollow a user: A user should be able to unfollow another user. After unfollowing, the tweets of the unfollowed user should no longer appear in the news feed.
// Limit the news feed: The news feed should be limited to showing only the 10 most recent tweets across the user and their followees.
// Class Design:
// You should design a Twitter class that supports the following methods:

// void postTweet(int userId, int tweetId, const string& tweetText): Compose a new tweet with tweetId and tweetText for the user with userId. Each tweet has a unique tweetId and a timestamp.
// vector<pair<int, string>> getNewsFeed(int userId): Retrieve the 10 most recent tweets in the user’s news feed. The tweets must be from the user themself and from the users they follow, ordered from most recent to least recent.
// void follow(int followerId, int followeeId): The user with followerId starts following the user with followeeId.
// void unfollow(int followerId, int followeeId): The user with followerId unfollows the user with followeeId.

//TC
// postTweet: O(1)
// getNewsfeed: O(k log k) where k no of tweets invloved
// follow and unfollow: O(1)


#include <bits/stdc++.h>
using namespace std;

class Twitter {
private:
    // Tweet structure to hold tweetId, timestamp, and text
    struct Tweet {
        int tweetId;
        int timestamp;
        string tweetText;
        Tweet(int id, int time, const string& text) : tweetId(id), timestamp(time), tweetText(text) {}
    };

    // Comparator for priority queue to compare based on timestamp
    struct CompareTweet {
        bool operator()(const Tweet& a, const Tweet& b) {
            return a.timestamp < b.timestamp; // Max-heap: more recent first
        }
    };

    // Time to track order of tweets
    int time;

    // User -> list of tweets (each tweet has a tweetId, timestamp, and text)
    unordered_map<int, vector<Tweet>> userTweets;

    // User -> set of followees
    unordered_map<int, unordered_set<int>> userFollowees;

public:
    // Constructor to initialize Twitter
    Twitter() {
        time = 0;
    }

    // Post a new tweet with tweet text
    void postTweet(int userId, int tweetId, const string& tweetText) {
        // Insert the tweet into the user's tweet list with the current time
        userTweets[userId].emplace_back(tweetId, time++, tweetText);
    }

    // Retrieve the 10 most recent tweets in the user's news feed
    vector<pair<int, string>> getNewsFeed(int userId) {
        // Use a max heap to get the most recent tweets from the user and their followees
        priority_queue<Tweet, vector<Tweet>, CompareTweet> maxHeap;

        // Add user's own tweets to the heap
        for (const auto& tweet : userTweets[userId]) {
            maxHeap.push(tweet);
        }

        // Add tweets from the followees
        if (userFollowees.find(userId) != userFollowees.end()) {
            for (const auto& followeeId : userFollowees[userId]) {
                for (const auto& tweet : userTweets[followeeId]) {
                    maxHeap.push(tweet);
                }
            }
        }

        // Retrieve the 10 most recent tweets
        vector<pair<int, string>> newsFeed;
        int count = 0;
        while (!maxHeap.empty() && count < 10) {
            const Tweet& topTweet = maxHeap.top();
            newsFeed.push_back({topTweet.tweetId, topTweet.tweetText});
            maxHeap.pop();
            count++;
        }

        return newsFeed;
    }

    // Follow a user
    void follow(int followerId, int followeeId) {
        // A user cannot follow themselves
        if (followerId != followeeId) {
            userFollowees[followerId].insert(followeeId);
        }
    }

    // Unfollow a user
    void unfollow(int followerId, int followeeId) {
        // Remove the followee if the user is following them
        if (userFollowees.find(followerId) != userFollowees.end()) {
            userFollowees[followerId].erase(followeeId);
        }
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId, tweetId, tweetText);
 * vector<pair<int, string>> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId, followeeId);
 * obj->unfollow(followerId, followeeId);
 */

int main() {
    Twitter obj;
    obj.postTweet(1, 101, "Hello World!");
    obj.postTweet(2, 102, "Good Morning!");
    obj.follow(1, 2);
    vector<pair<int, string>> feed = obj.getNewsFeed(1);

    // Print the news feed
    for (auto it : feed) {
        cout << it.first << " " << it.second << endl;
    }

    return 0;
}
