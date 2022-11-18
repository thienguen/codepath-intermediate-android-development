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
public class DefaultMovieViewHolder extends RecyclerView.ViewHolder {

    @Nullable
    @BindView(R.id.ivPosterPath)
    public ImageView vPosterPath;

    @BindView(R.id.tvOverview)
    public TextView vOverview;

    @BindView(R.id.tvTitle)
    public TextView vTitle;

    @Nullable
    @BindView(R.id.ivBackdropPath)
    public ImageView vBackdropPath;


    public DefaultMovieViewHolder(View itemView) {
        super(itemView);
        ButterKnife.bind(this, itemView);
    }



}
