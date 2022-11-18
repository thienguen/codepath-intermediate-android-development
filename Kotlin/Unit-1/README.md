# Android Project 1 - Simple Wordle Game

Submitted by: Thien Nguyen

Guess the World is an android app that recreates a simple version of the popular word game [Wordle](https://www.nytimes.com/games/wordle/index.html). 

Time spent: **8** hours spent in total

## Required Features

The following **required** functionality is completed:

- [x] **User has 3 chances to guess a random 4 letter word**
- [x] **After 3 guesses, user should no longer be able to submit another guess**
- [x] **After each guess, user sees the "correctness" of the guess**
- [x] **After all guesses are taken, user can see the target word displayed**

The following **optional** features are implemented:

- [ ] User can toggle betweeen different word lists
- [x] User can see the 'correctness' of their guess through colors on the word 
- [x] User sees a visual change after guessing the correct word
- [x] User can tap a 'Reset' button to get a new word and clear previous guesses
- [x] User will get an error message if they input an invalid guess
- [ ] User can see a 'streak' record of how many words they've guessed correctly.

The following **additional** features are implemented:

- [x] After getting a correct guess, user can have a little reward as conffeti after they pressed the button

## Video Walkthrough

Here's a walkthrough of implemented user stories:

This will be a regular walkthrough.

<img src='http://g.recordit.co/4yvdtqIBev.gif' title='Video Walkthrough' width='' alt='Video Walkthrough' />

This shown the reward if you get the correct guessed.

<img src='http://g.recordit.co/v0AhRfmuAG.gif' title='Video Walkthrough' width='' alt='Video Walkthrough' />

GIF created with recordit.co for Window

## Notes

The app was not hard to create, I have an issue when bumping into Kotlin syntax and the IDE keeps sending weird errors. The hardest part is configuring the confetti as I go with a different approach compared to the one suggested in CodePath. It was truly a satisfying moment when you get it done. And I have so many questions about the color and the usage of Scannable due to the pass-by value (if I use the helper function provided) the color won't appear in the app. And better ways to do this assignment. I do curious how other people approach this assignment as well

## License

    Copyright [2022] [Thien Nguyen]

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
