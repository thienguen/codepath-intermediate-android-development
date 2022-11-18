#Assignment 1: **CodePath-Flixtr**

**CodePath-Flixtr** is an android app that allows a read-only movie listing app using the Movie Database API.

Submitted by: **Alisha Alam**

Time spent: **35** hours spent in total

## User Stories

The following **required** functionality is completed:

* [x] User can view a list of movies (title, poster image, and overview) currently playing in theaters from the Movie Database API.
* [x] Lists should be fully optimized for performance with the ViewHolder pattern.
* [x] Views should be responsive for both landscape/portrait mode.
* [x] In portrait mode, the poster image, title, and movie overview is shown.
* [x] In landscape mode, the rotated layout should use the backdrop image instead and show the title and movie overview to the right of it.

The following **optional** features have been implemented:

* [ ] Add pull-to-refresh for popular stream with SwipeRefreshLayout (1 point)
* [x] ImproveDisplay a nice default placeholder graphic for each image during loading (1 point)
* [x] Improve the user interface through styling and coloring (1 to 5 points depending on the difficulty of UI improvements)
* [x] For popular movies (i.e. a movie voted for more than 5 stars), the full backdrop image is displayed. Otherwise, a poster image, the movie title, and overview is listed. Use Heterogenous ListViews and use different ViewHolder layout files for popular movies and less popular ones.

The following **stretch** features have been implemented:
* [x] Expose details of movie (ratings using RatingBar, popularity, and synopsis) in a separate activity.
* [x] Allow video posts to be played in full-screen using the YouTubePlayerView
* [x] When clicking on a popular movie (i.e. a movie voted for more than 5 stars) the video should be played immediately.
* [x] Less popular videos rely on the detailed page should show an image preview that can initiate playing a YouTube video.
* [x] Add a play icon overlay to popular movies to indicate that the movie can be played
* [ ] Leverage the data binding support module to bind data into one or more activity layout templates.
* [x] Apply the popular ButterKnife annotation library to reduce view boilerplate. 
* [x] Add a rounded corners for the images using the Picasso transformations. 


## Video Walkthrough 

Here's a walkthrough of implemented user stories:
## Flixtr in Portrait Mode

<img src='https://github.com/alishaalam/CodePath-Flixtr/blob/18d02a52befbf0f8b53ce07412da4aa207477e19/Flixtr_Portrait.gif' title='FLixtr_Portrait Video Walkthrough' width='' alt='Video Walkthrough' />

## Flixtr in Landscape Mode

<img src='https://github.com/alishaalam/CodePath-Flixtr/blob/356bf9b04dc62b08c0b022b2d2d254ce41e76138/Flixtr_Landscape.gif' title='FLixtr_Portrait Video Walkthrough' width='' alt='Video Walkthrough' />


## Notes
* [x] Added support for sorting movies based on Popularity, Date Released & Title
* [x] Added support for marking a movie as favorite using the floating action button, in the movie detail activity.
* [x] Used the Day/Night Appcompat theme. The theme is applied in the Detail Activity.
* [x] Added support for Recycler view
* [x] Each movie is represented using a CardView


## License

    Copyright [2016] [Alisha Alam]

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0
