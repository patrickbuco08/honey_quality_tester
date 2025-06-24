<?php

use Illuminate\Support\Facades\Route;
use Bocum\Http\Controllers\Auth\LoginController;
use Bocum\Http\Controllers\HomeController;
use Bocum\Http\Controllers\DashboardController;
use Bocum\Http\Controllers\Api\HoneySampleController;

// Home Routes
Route::get('/', [HomeController::class, 'index'])->name('home');

// Dashboard Routes

// Authentication Routes
Route::get('/login', [LoginController::class, 'showLoginForm'])->name('login')->middleware('guest');
Route::post('/login', [LoginController::class, 'login']);
Route::post('/logout', [LoginController::class, 'logout'])->name('logout');

// Protected Routes
Route::middleware(['auth'])->group(function () {
    Route::get('/dashboard', [DashboardController::class, 'index'])->name('dashboard');
    Route::get('/latest-honey-sample', [DashboardController::class, 'latest'])->name('latest.honey.sample');
    Route::patch('/honey-samples/{id}/name', [HoneySampleController::class, 'updateName']);
    Route::get('/samples/export', [HoneySampleController::class, 'export'])->name('samples.export');
});
