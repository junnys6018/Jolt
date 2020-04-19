#pragma once
#include "pch.h"
#include <glad/glad.h>

namespace Jolt
{
    // Maps a material to a block of indices
    template<typename Mat>
    class MaterialMapper
    {
    public:
        MaterialMapper(std::shared_ptr<Mat> material, GLuint startindex, GLuint endindex)
            :m_Material(material), m_StartIndex(startindex), m_EndIndex(endindex)
        {

        }

        MaterialMapper(const MaterialMapper& other)
            :m_Material(other.m_Material), m_StartIndex(other.m_StartIndex), m_EndIndex(other.m_EndIndex)
        {

        }

        inline std::shared_ptr<Mat> GetMaterial()
        {
            return m_Material;
        }

        inline GLuint Begin()
        {
            return m_StartIndex;
        }

        inline GLuint End()
        {
            return m_EndIndex;
        }
    private:
        std::shared_ptr<Mat> m_Material;
        GLuint m_StartIndex, m_EndIndex; // m_EndIndex denotes one past the last index to be mapped
    };
}