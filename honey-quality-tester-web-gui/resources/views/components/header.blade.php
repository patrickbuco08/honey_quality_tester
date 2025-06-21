<header class="bg-white shadow">
    <div class="container mx-auto px-4 py-4 flex justify-between items-center">
        <h1 class="text-xl font-bold text-honey">
            {{ $title ?? 'Honey Quality Tester' }}
        </h1>

        @auth
            <div x-data="{ open: false }" class="relative inline-block text-left">
                <div>
                    <button type="button" @click="open = !open"
                        class="inline-flex items-center gap-x-1.5 rounded-md bg-white px-3 py-2 text-sm font-semibold text-gray-900 focus:outline-none"
                        id="menu-button" aria-expanded="true" aria-haspopup="true">
                        {{ auth()->user()->name }}
                        <svg class="-mr-1 size-5 text-gray-400" viewBox="0 0 20 20" fill="currentColor" aria-hidden="true"
                            data-slot="icon">
                            <path fill-rule="evenodd"
                                d="M5.22 8.22a.75.75 0 0 1 1.06 0L10 11.94l3.72-3.72a.75.75 0 1 1 1.06 1.06l-4.25 4.25a.75.75 0 0 1-1.06 0L5.22 9.28a.75.75 0 0 1 0-1.06Z"
                                clip-rule="evenodd" />
                        </svg>
                    </button>
                </div>

                <div x-show="open" @click.away="open = false"
                    class="absolute right-0 z-10 mt-2 w-36 origin-top-right rounded-md bg-white shadow-lg ring-1 ring-black/5 focus:outline-hidden"
                    role="menu" aria-orientation="vertical" aria-labelledby="menu-button" tabindex="-1">
                    <div class="py-1" role="none">
                        <form method="POST" action="{{ route('logout') }}" role="none">
                            @csrf
                            <button type="submit" class="block w-full px-4 py-2 text-center text-sm text-gray-700"
                                role="menuitem" tabindex="-1" id="menu-item-3">Sign out</button>
                        </form>
                    </div>
                </div>
            </div>
        @endauth
    </div>
</header>
