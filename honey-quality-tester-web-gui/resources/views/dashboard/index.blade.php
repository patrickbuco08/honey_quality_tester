@extends('layouts.app')

@section('title', 'Dashboard')

@section('content')
    <div class="pt-20 flex flex-col gap-6">
        <div class="bg-white shadow-md rounded-2xl p-6">
            <h3 class="text-lg font-semibold text-gray-800">Sensor Readings</h3>
            <div class="grid grid-cols-2 md:grid-cols-4 gap-4 mt-4">
                <div>
                    <label class="block text-sm text-gray-600 mb-1">pH Value:</label>
                    <p class="w-full border rounded px-3 py-2 bg-gray-100">{{ $sample->data['sensor_readings']['ph_value'] ?? 'N/A' }}</p>
                </div>
                <div>
                    <label class="block text-sm text-gray-600 mb-1">EC Value (uS/cm):</label>
                    <p class="w-full border rounded px-3 py-2 bg-gray-100">{{ $sample->data['sensor_readings']['ec_value'] ?? 'N/A' }}</p>
                </div>
                <div>
                    <label class="block text-sm text-gray-600 mb-1">Moisture (%):</label>
                    <p class="w-full border rounded px-3 py-2 bg-gray-100">{{ $sample->data['sensor_readings']['moisture'] ?? 'N/A' }}</p>
                </div>
                <div>
                    <label class="block text-sm text-gray-600 mb-1">Spectroscopy Moisture (%):</label>
                    <p class="w-full border rounded px-3 py-2 bg-gray-100">{{ $sample->data['sensor_readings']['spectroscopy_moisture'] ?? 'N/A' }}</p>
                </div>
            </div>
        </div>
        <div class="bg-white shadow-md rounded-2xl p-6">
            <h3 class="text-lg font-semibold text-gray-800">Ambient Reading</h3>
            <div class="grid grid-cols-2 md:grid-cols-2 gap-4 mt-4">
                <div>
                    <label class="block text-sm text-gray-600 mb-1">Temperature (°C):</label>
                    <p class="w-full border rounded px-3 py-2 bg-gray-100">{{ $sample->data['ambient_reading']['temperature'] ?? 'N/A' }}</p>
                </div>
                <div>
                    <label class="block text-sm text-gray-600 mb-1">Relative Humidity (%):</label>
                    <p class="w-full border rounded px-3 py-2 bg-gray-100">{{ $sample->data['ambient_reading']['humidity'] ?? 'N/A' }}</p>
                </div>
            </div>
        </div>
        <div class="bg-white shadow-md rounded-2xl p-6">
            <h3 class="text-lg font-semibold text-gray-800">Absorbance Readings</h3>
            <div class="grid grid-cols-2 md:grid-cols-5 gap-4 mt-4">
                <div><label class="text-sm block mb-1">Violet Ch1:</label>
                    <p class="w-full border px-2 py-1 rounded bg-gray-100">{{ $sample->data['absorbance_readings']['violet_ch1'] ?? 'N/A' }}</p>
                </div>
                <div><label class="text-sm block mb-1">Violet Ch2:</label>
                    <p class="w-full border px-2 py-1 rounded bg-gray-100">{{ $sample->data['absorbance_readings']['violet_ch2'] ?? 'N/A' }}</p>
                </div>
                <div><label class="text-sm block mb-1">Blue:</label>
                    <p class="w-full border px-2 py-1 rounded bg-gray-100">{{ $sample->data['absorbance_readings']['blue'] ?? 'N/A' }}</p>
                </div>
                <div><label class="text-sm block mb-1">Green Ch4:</label>
                    <p class="w-full border px-2 py-1 rounded bg-gray-100">{{ $sample->data['absorbance_readings']['green_ch4'] ?? 'N/A' }}</p>
                </div>
                <div><label class="text-sm block mb-1">Green Ch5:</label>
                    <p class="w-full border px-2 py-1 rounded bg-gray-100">{{ $sample->data['absorbance_readings']['green_ch5'] ?? 'N/A' }}</p>
                </div>
                <div><label class="text-sm block mb-1">Orange:</label>
                    <p class="w-full border px-2 py-1 rounded bg-gray-100">{{ $sample->data['absorbance_readings']['orange'] ?? 'N/A' }}</p>
                </div>
                <div><label class="text-sm block mb-1">Red Ch7:</label>
                    <p class="w-full border px-2 py-1 rounded bg-gray-100">{{ $sample->data['absorbance_readings']['red_ch7'] ?? 'N/A' }}</p>
                </div>
                <div><label class="text-sm block mb-1">Red Ch8:</label>
                    <p class="w-full border px-2 py-1 rounded bg-gray-100">{{ $sample->data['absorbance_readings']['red_ch8'] ?? 'N/A' }}</p>
                </div>
                <div><label class="text-sm block mb-1">Clear:</label>
                    <p class="w-full border px-2 py-1 rounded bg-gray-100">{{ $sample->data['absorbance_readings']['clear'] ?? 'N/A' }}</p>
                </div>
                <div><label class="text-sm block mb-1">Near-IR:</label>
                    <p class="w-full border px-2 py-1 rounded bg-gray-100">{{ $sample->data['absorbance_readings']['near_ir'] ?? 'N/A' }}</p>
                </div>
            </div>
        </div>
    </div>
@endsection
