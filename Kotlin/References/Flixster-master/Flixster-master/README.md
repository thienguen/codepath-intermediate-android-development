# Flix
Flix is an app that allows users to browse movies from the [The Movie Database API](http://docs.themoviedb.apiary.io/#).

## Flix Part 2
#### REQUIRED (10pts)

- [X] (8pts) Expose details of movie (ratings using RatingBar, popularity, and synopsis) in a separate activity.
- [X] (2pts) Allow video posts to be played in full-screen using the YouTubePlayerView.

#### BONUS

- [ ] Implement a shared element transition when user clicks into the details of a movie (1 point).
- [ ] Trailers for popular movies are played automatically when the movie is selected (1 point).
  - [ ] When clicking on a popular movie (i.e. a movie voted for more than 5 stars) the video should be played immediately.
  - [ ] Less popular videos rely on the detailed page should show an image preview that can initiate playing a YouTube video.
- [ ] Add a play icon overlay to popular movies to indicate that the movie can be played (1 point).
- [ ] Apply data binding for views to help remove boilerplate code. (1 point)
- [X] Add a rounded corners for the images using the Glide transformations. (1 point)

### App Walkthough GIF

<img src="https://media0.giphy.com/media/n30Jgb3a2cmXC7NSPu/giphy.gif?cid=790b76110feb2d1d480056cb61c7b9b3391d8116e560751d&rid=giphy.gif&ct=g" width=250><br>

### Notes
My biggest challenge while working on part 2 was, trying to get YoutubePlayerView to work. My app kept crashing everytime I attempted to watch the trailer video, and I got the error "E/YouTubeAndroidPlayerAPI: Embed config is not supported in RemoteEmbeddedPlayer." I searched on Google, and looked at stack overflow posts about this issue, but could not find a helpful solution. The video do not load on Android API 27, and at least loads on API 30. I have played around with the layout height of the youtube video in the layout file, and finally got it to work without crashing the app. However, unfortunately videos are not exactly centered. I checked videos on YouTube app, and the same issues persist on the Youtube App as well. I could not find a solution to this problem.

## Open-source libraries used
- [Android Async HTTP](https://github.com/codepath/CPAsyncHttpClient) - Simple asynchronous HTTP requests with JSON parsing
- [Glide](https://github.com/bumptech/glide) - Image loading and caching library for Android

---

## Flix Part 1

### User Stories

#### REQUIRED (10pts)
- [X] (10pts) User can view a list of movies (title, poster image, and overview) currently playing in theaters from the Movie Database API.

#### BONUS
- [X] (2pts) Views should be responsive for both landscape/portrait mode.
   - [X] (1pt) In portrait mode, the poster image, title, and movie overview is shown.
   - [X] (1pt) In landscape mode, the rotated alternate layout should use the backdrop image instead and show the title and movie overview to the right of it.

- [X] (2pts) Display a nice default [placeholder graphic](https://guides.codepath.org/android/Displaying-Images-with-the-Glide-Library#advanced-usage) for each image during loading
- [X] (2pts) Improved the user interface by experimenting with styling and coloring.
- [ ] (2pts) For popular movies (i.e. a movie voted for more than 5 stars), the full backdrop image is displayed. Otherwise, a poster image, the movie title, and overview is listed. Use Heterogenous RecyclerViews and use different ViewHolder layout files for popular movies and less popular ones.

### App Walkthough GIF

<img src="https://media2.giphy.com/media/RGIpcprM3ErrNdiuhM/giphy.gif?cid=790b761134579e601a295d98a9339a55665d52ebccb6a99d&rid=giphy.gif&ct=g" width=500><br>

### Notes
My biggest challenge was figuring out how to put placeholder pictures via R.drawable. I first attempted to create a shape on drawable creating a new xml file, because first time I added a picture did not work for some reason. After I gave my IDE some time, I could use the image as placeholder image. My other challenge was I had difficulty understanding Heterogeneous Layouts inside RecyclerView. Reading about Heterogeneous Layouts inside RecyclerView on Codepath helped me understand a lot better.


### Open-source libraries used

- [Android Async HTTP](https://github.com/codepath/CPAsyncHttpClient) - Simple asynchronous HTTP requests with JSON parsing
- [Glide](https://github.com/bumptech/glide) - Image loading and caching library for Androids
