<?php

namespace Bocum\Http\Controllers;

use Bocum\Models\HoneySample;

class DashboardController extends Controller
{
    public function index()
    {
        $latestSample = HoneySample::latest()->first();

        return view('dashboard.index', [
            'sample' => $latestSample,
        ]);
    }
}
