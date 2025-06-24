<?php

namespace Bocum\Exports;

use Bocum\Models\HoneySample;
use Maatwebsite\Excel\Concerns\FromCollection;
use Maatwebsite\Excel\Concerns\WithHeadings;

class HoneySamplesExport implements FromCollection, WithHeadings
{
    public function collection()
    {
        return HoneySample::all()->map(function ($sample) {
            $data = $sample->data;

            return [
                'ID' => $sample->id,
                'Name' => $sample->name,
                'Temperature' => $data['ambient_reading']['temperature'] ?? null,
                'Humidity' => $data['ambient_reading']['humidity'] ?? null,
                'EC (μS/cm)' => $data['sensor_readings']['ec_value'] ?? null,
                'Moisture (%)' => $data['sensor_readings']['moisture'] ?? null,
                'pH' => $data['sensor_readings']['ph_value'] ?? null,
                'Spectroscopy Moisture' => $data['sensor_readings']['spectroscopy_moisture'] ?? null,
                'Blue' => $data['absorbance_readings']['blue'] ?? null,
                'Clear' => $data['absorbance_readings']['clear'] ?? null,
                'Orange' => $data['absorbance_readings']['orange'] ?? null,
                'Near IR' => $data['absorbance_readings']['near_ir'] ?? null,
                'Red CH7' => $data['absorbance_readings']['red_ch7'] ?? null,
                'Red CH8' => $data['absorbance_readings']['red_ch8'] ?? null,
                'Green CH4' => $data['absorbance_readings']['green_ch4'] ?? null,
                'Green CH5' => $data['absorbance_readings']['green_ch5'] ?? null,
                'Violet CH1' => $data['absorbance_readings']['violet_ch1'] ?? null,
                'Violet CH2' => $data['absorbance_readings']['violet_ch2'] ?? null,
                'Created At' => $sample->created_at ? $sample->created_at->format('M d, Y h:i A') : null,
            ];
        });
    }

    public function headings(): array
    {
        return [
            'ID', 'Name', 'Temperature', 'Humidity', 'EC (μS/cm)', 'Moisture (%)', 'pH', 'Spectroscopy Moisture',
            'Blue', 'Clear', 'Orange', 'Near IR', 'Red CH7', 'Red CH8',
            'Green CH4', 'Green CH5', 'Violet CH1', 'Violet CH2', 'Created At',
        ];
    }
}
