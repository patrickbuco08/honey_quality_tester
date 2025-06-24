<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <meta name="csrf-token" content="{{ csrf_token() }}">
    <title>@yield('title', 'Honey Quality Tester')</title>
    <link rel="icon" href="{{ asset('favicon.ico') }}" type="image/x-icon">
    @viteReactRefresh
    @vite(['resources/css/app.css', 'resources/js/app.jsx'])
    <script defer src="https://cdn.jsdelivr.net/npm/alpinejs@3.x.x/dist/cdn.min.js"></script>
</head>

<body class="bg-gray-100 text-gray-900 font-sans leading-relaxed tracking-wide">
    <x-header title="Honey Quality Tester" />
    <main class="w-full container mx-auto px-4">
        @yield('content')
    </main>
    <x-footer />
    @stack('scripts')
</body>

</html>
