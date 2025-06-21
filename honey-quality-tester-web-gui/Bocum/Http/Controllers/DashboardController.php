<?php

namespace Bocum\Http\Controllers;

use Bocum\Models\HoneySample;
use Illuminate\Http\JsonResponse;

class DashboardController extends Controller
{
    public function index()
    {
        $samples = HoneySample::latest()->paginate(1);
        $latestId = HoneySample::latest()->value('id');

        return view('dashboard.index', [
            'samples' => $samples,
            'latestId' => $latestId,
        ]);
    }

    public function latest(): JsonResponse
    {
        $latest = HoneySample::latest()->first();

        return response()->json([
            'success' => true,
            'sample' => $latest,
        ]);
    }
}
