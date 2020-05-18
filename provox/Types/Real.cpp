#include "pch.h"
#include "Real.h"

// I annoyingly have to put Float function declarations dealing with Doubles here, or do a bunch of weird hacks.
// This seemed easier.

Float::Float(const Double& value) : m_value(static_cast<float>(value.GetFP()))
{

}