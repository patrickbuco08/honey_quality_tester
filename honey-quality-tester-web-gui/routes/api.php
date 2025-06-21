<?php

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Route;
use Bocum\Http\Controllers\Api\HoneySampleController;

Route::get('/user', function (Request $request) {
    return $request->user();
})->middleware('auth:sanctum');

Route::middleware('api.token')->post('/honey-samples', [HoneySampleController::class, 'store']);
