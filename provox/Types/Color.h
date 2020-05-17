#pragma once

class Color
{
public:
	static Float FloatValueFromByte(uint8 c)
	{
		return Float(c).Divide(255.0f);
	}

	static Double DoubleValueFromByte(uint8 c)
	{
		return Double(c).Divide(255.0);
	}

	static uint8 ByteValueFromFloat(Float f)
	{
		return static_cast<uint8>(f.Multiply(255.0f));
	}

	static uint8 ByteValueFromDouble(Double d)
	{
		return static_cast<uint8>(d.Multiply(255.0));
	}

	static void ColorToHSL(Color& color, uint8* hue, uint8* saturation, uint8* luminance);
	static Color ColorFromHSL(uint8 hue, uint8 saturation, uint8 luminance, uint8 alpha = 255);

	static void ColorToHSV(Color& color, uint8* hue, uint8* saturation, uint8* value);
	static Color ColorFromHSV(uint8 hue, uint8 saturation, uint8 value, uint8 alpha = 255);

	Color() : m_r(0), m_g(0), m_b(0), m_a(255) {}

	Color(uint8 r, uint8 g, uint8 b, uint8 a) : 
		m_r(r), m_g(g), m_b(b), m_a(a) {}

	Color(Float r, Float g, Float b, Float a) :
		m_r(ByteValueFromFloat(r)), 
		m_g(ByteValueFromFloat(g)), 
		m_b(ByteValueFromFloat(b)), 
		m_a(ByteValueFromFloat(a)) {}

	Color(Double r, Double g, Double b, Double a) :
		m_r(ByteValueFromDouble(r)),
		m_g(ByteValueFromDouble(g)),
		m_b(ByteValueFromDouble(b)),
		m_a(ByteValueFromDouble(a)) {}

	// Getters
	uint8 GetRed() { return m_r; }
	uint8 GetGreen() { return m_g; }
	uint8 GetBlue() { return m_b; }
	uint8 GetAlpha() { return m_a; }

	Float GetRedF() { return FloatValueFromByte(m_r); }
	Float GetGreenF() { return FloatValueFromByte(m_g); }
	Float GetBlueF() { return FloatValueFromByte(m_b); }
	Float GetAlphaF() { return FloatValueFromByte(m_a); }

	Double GetRedFD() { return DoubleValueFromByte(m_r); }
	Double GetGreenFD() { return DoubleValueFromByte(m_g); }
	Double GetBlueFD() { return DoubleValueFromByte(m_b); }
	Double GetAlphaFD() { return DoubleValueFromByte(m_a); }

	// Setters
	void SetRed(uint8 r) { m_r = r; }
	void SetGreen(uint8 g) { m_g = g; }
	void SetBlue(uint8 b) { m_b = b; }
	void SetAlpha(uint8 a) { m_a = a; }

	void SetRedF(Float r) { m_r = ByteValueFromFloat(r); }
	void SetGreenF(Float g) { m_g = ByteValueFromFloat(g); }
	void SetBlueF(Float b) { m_b = ByteValueFromFloat(b); }
	void SetAlphaF(Float a) { m_a = ByteValueFromFloat(a); }

	// Conversion
	void ToHSL(uint8* hue, uint8* saturation, uint8* luminance)
	{
		ColorToHSL(*this, hue, saturation, luminance);
	}

	void FromHSL(uint8 hue, uint8 saturation, uint8 luminance)
	{
		*this = ColorFromHSL(hue, saturation, luminance);
	}

	void ToHSV(uint8* hue, uint8* saturation, uint8* value)
	{

	}

	void FromHSV(uint8* hue, uint8* saturation, uint8* value)
	{

	}

private:
	uint8 m_r;
	uint8 m_g;
	uint8 m_b;
	uint8 m_a;
};