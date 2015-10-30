#pragma once

#include <vector>
#include <string>
#include <iostream>

#include <QProgressBar>


//-------------------------------------------------------------------------------------------------
// Voxel
//-------------------------------------------------------------------------------------------------

class Voxel
{
	public:

		Voxel();
		Voxel(const Voxel &other);
		Voxel(const float value);

		~Voxel();


		// VOXEL VALUE

		void					setValue(const float value);
        float				getValue() const;


		// OPERATORS

        bool                    operator==(const Voxel &other) const;
        bool                    operator!=(const Voxel &other) const;
        bool                    operator>(const Voxel &other) const;
        bool                    operator>=(const Voxel &other) const;
        bool                    operator<(const Voxel &other) const;
        bool                    operator<=(const Voxel &other) const;

		const Voxel				operator+(const Voxel &other) const;
		const Voxel				operator-(const Voxel &other) const;
		const Voxel				operator*(const float &value) const;
		const Voxel				operator/(const float &value) const;
		
		const Voxel&			operator+=(const Voxel &other);
		const Voxel&			operator-=(const Voxel &other);
		const Voxel&			operator*=(const float &value);
		const Voxel&			operator/=(const float &value);


	private:

		float					m_Value;

};


//-------------------------------------------------------------------------------------------------
// Volume
//-------------------------------------------------------------------------------------------------

class Volume
{

	public:

		Volume();
		~Volume();


		// VOLUME DATA

		const Voxel&			voxel(const int i) const;
		const Voxel&			voxel(const int x, const int y, const int z) const;
		const Voxel*			voxels() const;

        int                     width() const;
        int                     height() const;
        int                     depth() const;

        int                     size() const;

		bool					loadFromFile(QString filename, QProgressBar* progressBar);


	private:


		int						m_Width;
		int						m_Height;
		int						m_Depth;

		int						m_Size;

        std::vector<Voxel>		m_Voxels;
};
