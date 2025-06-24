<?php

namespace Bocum\Http\Controllers\Api;

use Bocum\Http\Controllers\Controller;
use Illuminate\Http\Request;
use Bocum\Models\HoneySample;

class HoneySampleController extends Controller
{
    public function store(Request $request)
    {
        $request->validate([
            'data' => 'required|array',
        ]);

        $sample = HoneySample::create([
            'data' => $request->input('data'),
        ]);

        return response()->json([
            'message' => 'Sample stored successfully.',
            'id' => $sample->id,
        ], 201);
    }

    public function updateName(Request $request, $id)
    {
        $request->validate([
            'name' => 'required|string|max:255',
        ]);

        $sample = HoneySample::findOrFail($id);
        $sample->name = $request->input('name');
        $sample->save();

        return response()->json([
            'message' => 'Sample name updated successfully.',
            'id' => $sample->id,
            'name' => $sample->name,
        ]);
    }
}
