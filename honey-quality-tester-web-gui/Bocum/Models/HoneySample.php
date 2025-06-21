<?php

namespace Bocum\Models;

use Illuminate\Database\Eloquent\Model;

class HoneySample extends Model
{
    protected $fillable = ['data'];

    protected $casts = [
        'data' => 'array',
    ];
}
