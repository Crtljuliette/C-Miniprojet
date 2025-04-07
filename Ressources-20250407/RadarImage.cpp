#include <iostream>
#include <memory>

#include "RadarImage.h"

RadarImage::RadarImage(const std::string& filename) :
	m_filename{filename}
{
	std::unique_ptr<TinyTIFFReaderFile, typeof(&TinyTIFFReader_close)> file{
		TinyTIFFReader_open(filename.c_str()), &TinyTIFFReader_close
	};

	if (!file) {
		std::cerr << "Impossible d'ouvrir le fichier " << filename << "\n";
		return;
	}

	const uint32_t frames = TinyTIFFReader_countFrames(file.get());
	const uint32_t width = TinyTIFFReader_getWidth(file.get());
	const uint32_t height = TinyTIFFReader_getHeight(file.get());
	const uint16_t samples = TinyTIFFReader_getSamplesPerPixel(file.get());
	const uint16_t bitspersample = TinyTIFFReader_getBitsPerSample(file.get(), 0);

	if (TinyTIFFReader_wasError(file.get()) ||
	    frames != 1 ||
	    width <= 0 ||
	    height <= 0 ||
	    samples != 1 ||
	    bitspersample != 16) {
		std::cerr << "Le format du fichier n'est pas celui attendu\n";
		return;
	}

	m_width = width;
	m_height = height;

	m_data.resize(width*height);
	TinyTIFFReader_getSampleData_s(file.get(), m_data.data(), m_data.size() * 2, 0);


	if (TinyTIFFReader_wasError(file.get())) {
		std::cerr << "Impossible d'extraire les données du fichier\n";
		return;
	}

	m_valid = true;
}

float RadarImage::getMinLatitude() const
{
	return MIN_LATITUDE;
}

float RadarImage::getMaxLatitude() const
{
	return MAX_LATITUDE;
}

float RadarImage::getMinLongitude() const
{
	return MIN_LONGITUDE;
}

float RadarImage::getMaxLongitude() const
{
	return MAX_LONGITUDE;
}

int RadarImage::getWidth() const
{
	return m_width;
}

int RadarImage::getHeight() const
{
	return m_height;
}

bool RadarImage::isValid() const
{
	return m_valid;
}

uint16_t RadarImage::getDataAtPixel(int row, int column) const
{
	if (row < 0 || row >= m_height || column < 0 || column >= m_width) {
		std::cerr << "Pixel hors-limite " << row << "x" << column << "\n";
		return 0;
	}

	return m_data[row * m_height + column];
}

float RadarImage::getRainfallAtCoordinates(float lat, float lon) const
{
		// Verification des coordonnées
		if (lat < MIN_LATITUDE || lat > MAX_LATITUDE || 
				lon < MIN_LONGITUDE || lon > MAX_LONGITUDE) {
				std::cerr << "Coordinates out of bounds: lat=" << lat << ", lon=" << lon << "\n";
				return 0.0f;
		}

		// Calculer la ligne (north to south: row 0 is MAX_LATITUDE)
		// Orientation inversée (nord au sud)
		float latRange = MAX_LATITUDE - MIN_LATITUDE;
		int row = static_cast<int>((MAX_LATITUDE - lat) / latRange * m_height);

		// Calcule de la colonne (west to east: column 0 is MIN_LONGITUDE)
		float lonRange = MAX_LONGITUDE - MIN_LONGITUDE;
		int column = static_cast<int>((lon - MIN_LONGITUDE) / lonRange * m_width);

		// Valeur de la ligne et de la colonne dans les limites
		row = std::max(0, std::min(row, m_height - 1));
		column = std::max(0, std::min(column, m_width - 1));

		// Obtenir la valeur de la pluie à partir des données
		uint16_t rawData = getDataAtPixel(row, column);
		return rawData * CONVERSION_FACTOR;
}