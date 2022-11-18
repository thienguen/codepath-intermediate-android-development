package com.happytimes.alisha.flixtr.viewHolder;

import android.support.annotation.Nullable;
import android.support.v7.widget.RecyclerView;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import com.happytimes.alisha.flixtr.R;

import butterknife.BindView;
import butterknife.ButterKnife;

/**
 * Created by alishaalam on 7/19/16.
 */
public class PopularMovieViewHolder extends RecyclerView.ViewHolder {



    @BindView(R.id.ivBackdropPath)
    public ImageView vBackdropPath;

    @Nullable
    @BindView(R.id.tvOverview)
    public TextView vOverview;

    @Nullable
    @BindView(R.id.tvTitle)
    public TextView vTitle;

    public PopularMovieViewHolder(View itemView) {
        super(itemView);
        ButterKnife.bind(this, itemView);
    }
}
