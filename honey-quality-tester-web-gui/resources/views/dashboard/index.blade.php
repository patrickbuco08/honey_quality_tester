@extends('layouts.app')

@section('title', 'Dashboard')

@section('content')
    <div class="pt-10 flex flex-col gap-6" data-sample-id="{{ $latestId }}">
        
        <div class="bg-white shadow-md rounded-2xl p-6">
            <div id="rename-sample"></div>
            <div class="flex flex-row">
                <button onclick="document.getElementById('infoModal').classList.remove('hidden')"
                    class="flex items-center gap-2 text-sm text-gray-600 hover:text-yellow-600">
                    <svg xmlns="http://www.w3.org/2000/svg" class="h-4 w-4" fill="none" viewBox="0 0 24 24"
                        stroke="currentColor">
                        <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2"
                            d="M13 16h-1v-4h-1m1-4h.01M12 2a10 10 0 110 20 10 10 0 010-20z" />
                    </svg>
                    <span>Honey Standard Parameters</span>
                </button>
            </div>
            <p id="date-tested" class="text-gray-700">Date Tested: {{ $samples[0]->created_at->format('F j, Y g:i A') }}</p>
        </div>
        <div class="bg-white shadow-md rounded-2xl p-6">
            <h3 class="text-lg font-semibold text-gray-800">Sensor Readings</h3>
            <div class="grid grid-cols-1 md:grid-cols-2 gap-4 mt-4">
                <div>
                    <label class="block text-sm text-gray-600 mb-1">pH Value:</label>
                    <p id="sensor-ph_value" class="w-full border rounded px-3 py-2 bg-gray-100">
                        {{ $samples[0]->data['sensor_readings']['ph_value'] ?? 'N/A' }}</p>
                </div>
                <div>
                    <label class="block text-sm text-gray-600 mb-1">EC Value (uS/cm):</label>
                    <p id="sensor-ec_value" class="w-full border rounded px-3 py-2 bg-gray-100">
                        {{ $samples[0]->data['sensor_readings']['ec_value'] ?? 'N/A' }}</p>
                </div>
                <div>
                    <label class="block text-sm text-gray-600 mb-1">Moisture (%):</label>
                    <p id="sensor-moisture" class="w-full border rounded px-3 py-2 bg-gray-100">
                        {{ $samples[0]->data['sensor_readings']['moisture'] ?? 'N/A' }}</p>
                </div>
                <div>
                    <label class="block text-sm text-gray-600 mb-1">Spectroscopy Moisture (%):</label>
                    <p id="sensor-spectroscopy_moisture" class="w-full border rounded px-3 py-2 bg-gray-100">
                        {{ $samples[0]->data['sensor_readings']['spectroscopy_moisture'] ?? 'N/A' }}</p>
                </div>
            </div>
        </div>
        <div class="bg-white shadow-md rounded-2xl p-6">
            <h3 class="text-lg font-semibold text-gray-800">Ambient Reading</h3>
            <div class="grid grid-cols-1 md:grid-cols-2 gap-4 mt-4">
                <div>
                    <label class="block text-sm text-gray-600 mb-1">Temperature (°C):</label>
                    <p id="ambient-temperature" class="w-full border rounded px-3 py-2 bg-gray-100">
                        {{ $samples[0]->data['ambient_reading']['temperature'] ?? 'N/A' }}</p>
                </div>
                <div>
                    <label class="block text-sm text-gray-600 mb-1">Relative Humidity (%):</label>
                    <p id="ambient-humidity" class="w-full border rounded px-3 py-2 bg-gray-100">
                        {{ $samples[0]->data['ambient_reading']['humidity'] ?? 'N/A' }}</p>
                </div>
            </div>
        </div>
        <div class="bg-white shadow-md rounded-2xl p-6">
            <h3 class="text-lg font-semibold text-gray-800">Absorbance Readings</h3>
            <div class="grid grid-cols-1 md:grid-cols-5 gap-4 mt-4">
                <div><label class="text-sm block mb-1">Violet Ch1:</label>
                    <p id="absorbance-violet_ch1" class="w-full border px-2 py-1 rounded bg-gray-100">
                        {{ $samples[0]->data['absorbance_readings']['violet_ch1'] ?? 'N/A' }}</p>
                </div>
                <div><label class="text-sm block mb-1">Violet Ch2:</label>
                    <p id="absorbance-violet_ch2" class="w-full border px-2 py-1 rounded bg-gray-100">
                        {{ $samples[0]->data['absorbance_readings']['violet_ch2'] ?? 'N/A' }}</p>
                </div>
                <div><label class="text-sm block mb-1">Blue:</label>
                    <p id="absorbance-blue" class="w-full border px-2 py-1 rounded bg-gray-100">
                        {{ $samples[0]->data['absorbance_readings']['blue'] ?? 'N/A' }}</p>
                </div>
                <div><label class="text-sm block mb-1">Green Ch4:</label>
                    <p id="absorbance-green_ch4" class="w-full border px-2 py-1 rounded bg-gray-100">
                        {{ $samples[0]->data['absorbance_readings']['green_ch4'] ?? 'N/A' }}</p>
                </div>
                <div><label class="text-sm block mb-1">Green Ch5:</label>
                    <p id="absorbance-green_ch5" class="w-full border px-2 py-1 rounded bg-gray-100">
                        {{ $samples[0]->data['absorbance_readings']['green_ch5'] ?? 'N/A' }}</p>
                </div>
                <div><label class="text-sm block mb-1">Orange:</label>
                    <p id="absorbance-orange" class="w-full border px-2 py-1 rounded bg-gray-100">
                        {{ $samples[0]->data['absorbance_readings']['orange'] ?? 'N/A' }}</p>
                </div>
                <div><label class="text-sm block mb-1">Red Ch7:</label>
                    <p id="absorbance-red_ch7" class="w-full border px-2 py-1 rounded bg-gray-100">
                        {{ $samples[0]->data['absorbance_readings']['red_ch7'] ?? 'N/A' }}</p>
                </div>
                <div><label class="text-sm block mb-1">Red Ch8:</label>
                    <p id="absorbance-red_ch8" class="w-full border px-2 py-1 rounded bg-gray-100">
                        {{ $samples[0]->data['absorbance_readings']['red_ch8'] ?? 'N/A' }}</p>
                </div>
                <div><label class="text-sm block mb-1">Clear:</label>
                    <p id="absorbance-clear" class="w-full border px-2 py-1 rounded bg-gray-100">
                        {{ $samples[0]->data['absorbance_readings']['clear'] ?? 'N/A' }}</p>
                </div>
                <div><label class="text-sm block mb-1">Near-IR:</label>
                    <p id="absorbance-near_ir" class="w-full border px-2 py-1 rounded bg-gray-100">
                        {{ $samples[0]->data['absorbance_readings']['near_ir'] ?? 'N/A' }}</p>
                </div>
            </div>
        </div>
    </div>
    <div class="mt-6">
        {{ $samples->links() }}
    </div>

    <div id="infoModal" class="fixed inset-0 bg-black bg-opacity-40 flex justify-center sm:items-center z-50 hidden p-0">
        <div
            class="bg-white p-6 mt- md:mt-10 rounded-none shadow-lg sm:rounded-lg w-full max-w-xl sm:max-w-xl sm:w-full sm:mx-auto sm:my-auto h-full sm:h-auto overflow-y-auto sm:border border-0">
            <div class="flex justify-between items-center mb-4">
                <h2 class="text-lg font-semibold text-yellow-700">Classes of Honey for Honey Quality Tester</h2>
                <button onclick="document.getElementById('infoModal').classList.add('hidden')"
                    class="text-gray-600 hover:text-gray-700 text-2xl font-bold">&times;</button>
            </div>
            <table class="w-full text-left border border-gray-300 rounded-md shadow-md overflow-hidden">
                <thead class="bg-yellow-100 text-yellow-800">
                    <tr>
                        <th class="p-2 border border-gray-300">Moisture Content</th>
                        <th class="p-2 border border-gray-300">Electrical Conductivity</th>
                        <th class="p-2 border border-gray-300">pH Value</th>
                    </tr>
                </thead>
                <tbody class="text-sm text-gray-700">
                    <tr>
                        <td class="p-2 border border-gray-300">≤ 20% <em>(Apis mellifera and Apis cerana)</em></td>
                        <td class="p-2 border border-gray-300">&lt; 0.8 mS/cm (most honey)</td>
                        <td class="p-2 border border-gray-300">≥ 3.7</td>
                    </tr>
                    <tr>
                        <td class="p-2 border border-gray-300">≤ 23% <em>(Apis dorsata and Apis breviligula)</em></td>
                        <td class="p-2 border border-gray-300">&gt; 0.8 mS/cm (only for chestnut honey, honeydew honey
                            and their blend)</td>
                        <td class="p-2 border border-gray-300">≤ 4.5</td>
                    </tr>
                    <tr>
                        <td class="p-2 border border-gray-300">≤ 24% <em>(Tetragonula spp.)</em></td>
                        <td class="p-2 border border-gray-300"></td>
                        <td class="p-2 border border-gray-300"></td>
                    </tr>
                </tbody>
            </table>
            <p class="mt-4 text-sm text-red-600 italic">
                The values of parameters are based on the following studies/articles: <br />
                <strong>Moisture</strong> (BAFS 2022), <strong>Electrical Conductivity</strong> (BAFS 2022), and <strong>pH
                    Values</strong> (Codex Standard for Honey [CAC], 1981).
            </p>
        </div>
    </div>
@endsection

@push('scripts')
    <script type="module" src="{{ Vite::asset('resources/js/dashboard.js') }}"></script>
@endpush
