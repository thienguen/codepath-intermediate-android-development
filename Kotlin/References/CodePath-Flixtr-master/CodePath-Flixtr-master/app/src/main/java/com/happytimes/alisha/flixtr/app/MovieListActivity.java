package com.happytimes.alisha.flixtr.app;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;

import com.android.volley.Request;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.happytimes.alisha.flixtr.R;
import com.happytimes.alisha.flixtr.helper.JacksonRequest;
import com.happytimes.alisha.flixtr.helper.VolleySingleton;
import com.happytimes.alisha.flixtr.model.Movie;
import com.happytimes.alisha.flixtr.model.MovieCollection;
import com.happytimes.alisha.flixtr.model.MovieTrailer;
import com.happytimes.alisha.flixtr.model.TrailerCollection;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import butterknife.BindView;
import butterknife.ButterKnife;

public class MovieListActivity extends AppCompatActivity {

    public static boolean mTwoPane;
    MovieAdapter movieAdapter;
    List<Movie> moviesList = new ArrayList<>();

    private static final String TAG = MovieListActivity.class.getSimpleName();
    public static final String NOW_PLAYING_MOVIES_URL = "https://api.themoviedb.org/3/movie/now_playing?api_key=";
    public static final String MOVIE_HOST_URL= "https://api.themoviedb.org/3/movie/";
    public static final String MOVIE_TRAILER_URL= "/trailers?api_key=";
    public static final String API_KEY = "a07e22bc18f5cb106bfe4cc1f83ad8ed";

    public static final Map<String, Movie> MOVIE_MAP = new HashMap<>();

    @BindView(R.id.toolbar)
    Toolbar toolbar;

    @BindView(R.id.movie_list)
    RecyclerView recyclerView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_movie_list);

        ButterKnife.bind(this);

        //To reduce overdraw
        getWindow().setBackgroundDrawable(null);

        setSupportActionBar(toolbar);
        toolbar.setTitle(getTitle());

        initializeRecyclerView();

        getNowPlayingMovies(NOW_PLAYING_MOVIES_URL + API_KEY);

        if (findViewById(R.id.movie_detail_container) != null) {
            // The detail container view will be present only in the
            // large-screen layouts (res/values-w900dp).
            mTwoPane = true;
        }

    }

    private void initializeRecyclerView() {

        LinearLayoutManager llm = new LinearLayoutManager(this);
        llm.setOrientation(LinearLayoutManager.VERTICAL);
        recyclerView.setLayoutManager(llm);

        movieAdapter =  new MovieAdapter(this, moviesList);
        recyclerView.setAdapter(movieAdapter);
        recyclerView.setHasFixedSize(true);
        recyclerView.addOnItemTouchListener(new RecyclerTouchListener(getApplicationContext(), recyclerView, new ClickListener() {
            @Override
            public void onClick(View view, int position) {
                Movie mMovie = moviesList.get(position);
                if (mTwoPane) {
                    Bundle arguments = new Bundle();
                    arguments.putString(MovieDetailFragment.ARG_ITEM_ID, String.valueOf(mMovie.getId()));
                    MovieDetailFragment fragment = new MovieDetailFragment();
                    fragment.setArguments(arguments);
                    getSupportFragmentManager().beginTransaction()
                            .replace(R.id.movie_detail_container, fragment)
                            .commit();
                } else {
                    Context mContext = view.getContext();
                    Intent intent;
                    if(mMovie.isPopular()) {
                        intent = new Intent(mContext, QuickPlayActivity.class);
                    } else {
                        intent = new Intent(mContext, MovieDetailActivity.class);
                    }
                    intent.putExtra(MovieDetailFragment.ARG_ITEM_ID, String.valueOf(mMovie.getId()));
                    mContext.startActivity(intent);
                }
            }

            @Override
            public void onLongClick(View view, int position) {

            }
        }));
    }

    private void getNowPlayingMovies(String url) {

        JacksonRequest<MovieCollection> jacksonRequest = new JacksonRequest<>
                (Request.Method.GET, url, null, MovieCollection.class, new Response.Listener<MovieCollection>() {
                    @Override
                    public void onResponse(MovieCollection response) {
                        Log.d(TAG+"Response", response.toString());
                        parseNowPlayingMoviesResponse(response);
                    }

                }, new Response.ErrorListener() {

                    @Override
                    public void onErrorResponse(VolleyError error) {
                        error.printStackTrace();
                    }
                });

        // Adding a request (in this example, called jacksonRequest) to the RequestQueue.
        VolleySingleton.getInstance(this).addToRequestQueue(jacksonRequest, TAG);
    }

    private void parseNowPlayingMoviesResponse(MovieCollection response) {

        moviesList.addAll(response.getResults());
        displayDetails();
        addMoviesToMap();
        getMovieTrailerDetails(MOVIE_HOST_URL, moviesList, MOVIE_TRAILER_URL, API_KEY);
    }


    private void getMovieTrailerDetails(String movieHostUrl, List<Movie> moviesList, String movieTrailerUrl, String apiKey) {

        for (final Movie movie : moviesList) {
            String url = movieHostUrl + String.valueOf(movie.getId()) + movieTrailerUrl + apiKey;
            JacksonRequest<TrailerCollection> trailerRequest = new JacksonRequest<>
                    (Request.Method.GET, url, null, TrailerCollection.class, new Response.Listener<TrailerCollection>() {
                        @Override
                        public void onResponse(TrailerCollection response) {
                            Log.d(TAG, "Response: " + response.toString());
                            parseTrailerDetails(movie, response);
                        }

                    }, new Response.ErrorListener() {

                        @Override
                        public void onErrorResponse(VolleyError error) {
                            Log.e(TAG, "Trailer Error Response: " + error.getMessage());
                            error.printStackTrace();
                        }
                    });

            // Adding the request (in this example, called jacksonRequest) to the RequestQueue.
            VolleySingleton.getInstance(this).addToRequestQueue(trailerRequest, TAG);
        }

    }

    private void parseTrailerDetails(Movie movie, TrailerCollection response) {
        Log.d(TAG, response.toString());
        List<MovieTrailer> trailerList = response.getMovieTrailers();
        movie.setTrailers(trailerList);
    }

    private void addMoviesToMap() {
        for (Movie m : moviesList)
            MOVIE_MAP.put(String.valueOf(m.getId()), m);
    }

    private void displayDetails() {
        movieAdapter.notifyDataSetChanged();

    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return super.onCreateOptionsMenu(menu);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.menuSortPopularity:
                Collections.sort(moviesList, MoviePopularityDescComparator);
                movieAdapter.notifyDataSetChanged();
                return true;
            case R.id.menuSortDateReleased:
                Collections.sort(moviesList, MovieDateReleasedComparator);
                movieAdapter.notifyDataSetChanged();
                return true;
            case R.id.menuSortTitle:
                Collections.sort(moviesList, MovieTitleComparator);
                movieAdapter.notifyDataSetChanged();
                return true;

            default:
                return super.onOptionsItemSelected(item);
        }
    }

    public static Comparator<Movie> MoviePopularityDescComparator = new Comparator<Movie>() {

        public int compare(Movie m1, Movie m2) {
            return Double.compare(m2.getPopularity(), m1.getPopularity());
        }
    };

    public static Comparator<Movie> MovieTitleComparator = new Comparator<Movie>() {

        public int compare(Movie m1, Movie m2) {
            return m1.getTitle().compareToIgnoreCase(m2.getTitle());
        }
    };


    public static Comparator<Movie> MovieDateReleasedComparator = new Comparator<Movie>() {

        public int compare(Movie m1, Movie m2) {

            String date1 = m1.getReleaseDate();
            String date2 = m2.getReleaseDate();

            return date1.compareToIgnoreCase(date2);
        }
    };
}
