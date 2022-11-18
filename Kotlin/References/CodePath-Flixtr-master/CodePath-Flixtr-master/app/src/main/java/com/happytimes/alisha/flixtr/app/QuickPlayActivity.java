package com.happytimes.alisha.flixtr.app;

import android.os.Bundle;

import com.google.android.youtube.player.YouTubeBaseActivity;
import com.google.android.youtube.player.YouTubeInitializationResult;
import com.google.android.youtube.player.YouTubePlayer;
import com.google.android.youtube.player.YouTubePlayerView;
import com.happytimes.alisha.flixtr.R;
import com.happytimes.alisha.flixtr.model.Movie;

import butterknife.BindView;
import butterknife.ButterKnife;

/**
 * Created by alishaalam on 7/24/16.
 */
public class QuickPlayActivity extends YouTubeBaseActivity {

    @BindView(R.id.player)
    YouTubePlayerView youTubePlayerView;

    @Override
    protected void onCreate(Bundle bundle) {
        super.onCreate(bundle);
        setContentView(R.layout.activity_quick_play);
        ButterKnife.bind(this);

        youTubePlayerView.initialize(MovieListActivity.API_KEY,
                new YouTubePlayer.OnInitializedListener() {
                    @Override
                    public void onInitializationSuccess(YouTubePlayer.Provider provider,
                                                        YouTubePlayer youTubePlayer, boolean b) {

                        // do any work here to cue video, play video, etc.
                        String id = getIntent().getStringExtra(MovieDetailFragment.ARG_ITEM_ID);
                        Movie mMovie = MovieListActivity.MOVIE_MAP.get(id);

                        youTubePlayer.loadVideo(mMovie.getTrailers().get(0).getSource());
                    }
                    @Override
                    public void onInitializationFailure(YouTubePlayer.Provider provider,
                                                        YouTubeInitializationResult youTubeInitializationResult) {
                    }
                });
    }
}
