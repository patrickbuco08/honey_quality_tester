@extends('layouts.app')

@section('title', 'Honey Quality Tester')

@section('content')
    <section class="min-h-screen text-center pt-20">
        <h1 class="text-4xl md:text-5xl font-bold text-honey mb-6">
            Welcome to the Honey Quality Tester
        </h1>
        <p class="max-w-2xl mx-auto text-lg text-gray-700 mb-8">
            This platform helps beekeepers, researchers, and enthusiasts store and manage data from tested honey samples — making honey analysis easier, faster, and more reliable.
        </p>
        <p class="text-md text-gray-600">
            Already tested your honey? <a href="/login" class="text-honey font-medium hover:text-honey-dark underline">Log in here</a> to record and access your results.
        </p>
    </section>
@endsection
