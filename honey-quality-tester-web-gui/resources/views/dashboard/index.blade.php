@extends('layouts.app')

@section('title', 'Dashboard')

@section('content')
    <div class="pt-10 flex flex-col gap-6" data-sample-id="{{ $latestId }}">
        <div class="bg-white shadow-md rounded-2xl p-6">
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
@endsection

@push('scripts')
    <script type="module" src="{{ Vite::asset('resources/js/dashboard.js') }}"></script>
@endpush
