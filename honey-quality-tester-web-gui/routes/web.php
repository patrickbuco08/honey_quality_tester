<?php

use Illuminate\Support\Facades\Route;
use Bocum\Http\Controllers\Auth\LoginController;

// Authentication Routes
Route::get('/login', [LoginController::class, 'showLoginForm'])->name('login');
Route::post('/login', [LoginController::class, 'login']);
Route::post('/logout', [LoginController::class, 'logout'])->name('logout');

// Protected Routes
Route::middleware(['auth'])->group(function () {
    // Add your protected routes here
    Route::get('/dashboard', function () {
        return view('dashboard');
    })->name('dashboard');
});
