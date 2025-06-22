@extends('layouts.app')

@section('title', 'Login')

@section('content')

    <div class="min-h-screen flex items-center justify-center">
        <div class="bg-white shadow-xl rounded-2xl py-8 px-6 w-full max-w-md">
            <div class="text-center mb-6">
                <h1 class="text-3xl font-bold text-honey">Welcome Back</h1>
                <p class="text-gray-500 text-sm">Login to your account</p>
            </div>

            <form method="POST" action="{{ route('login') }}" class="space-y-5">
                @csrf

                <div>
                    <label for="email" class="block text-sm font-medium text-gray-700 mb-1">Email</label>
                    <input type="email" id="email" name="email" required
                        class="w-full px-4 py-2 border border-gray-300 rounded-lg focus:outline-none focus:ring-2 focus:ring-honey focus:border-transparent"
                        value="{{ old('email') }}">
                </div>

                <div>
                    <label for="password" class="block text-sm font-medium text-gray-700 mb-1">Password</label>
                    <input type="password" id="password" name="password" required
                        class="w-full px-4 py-2 border border-gray-300 rounded-lg focus:outline-none focus:ring-2 focus:ring-honey focus:border-transparent">
                </div>

                <div class="flex items-center justify-between text-sm">
                    <label class="flex items-center space-x-2">
                        <input type="checkbox" name="remember" class="form-checkbox text-honey rounded">
                        <span>Remember me</span>
                    </label>
                </div>

                <button type="submit"
                    class="w-full bg-honey text-white py-2 px-4 rounded-lg hover:bg-honey-dark transition duration-200">
                    Sign In
                </button>
            </form>
        </div>
    </div>

@endsection
