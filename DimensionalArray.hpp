#pragma once

#include "ArrayPointer.hpp"

namespace pankey {

    namespace DataStructure {

        namespace Array {

            template<class Policy, class IndexPolicy>
            class DimensionalArray : public ArrayPointer<Policy> {
                public:
                    using Base = ArrayPointer<Policy>;
                    using VALUE_TYPE = typename Base::VALUE_TYPE;
                    using SIZE_TYPE = typename Base::SIZE_TYPE;
                    
                    // Alias local para el manejo de índices N-dimensionales
                    using IndexArray = ArrayPointer<IndexPolicy>;
                    using INDEX_VALUE_TYPE = typename IndexArray::VALUE_TYPE; // Tipo entero (int, size_t, etc.)

                    using Base::set;
                    using Base::get;
                    using Base::getFast;

                    DimensionalArray() = default;

                    explicit DimensionalArray(const IndexArray& a_shape) {
                        create(a_shape);
                    }

                    bool create(const IndexArray& a_shape) {
                        if (a_shape.isEmpty()) {
                            clear();
                            return false;
                        }

                        SIZE_TYPE i_elementCount = 1;
                        for (SIZE_TYPE i = 0; i < a_shape.length(); ++i) {
                            const INDEX_VALUE_TYPE i_dimension = a_shape.getFast(i);
                            if (i_dimension <= 0) {
                                clear();
                                return false;
                            }
                            i_elementCount *= static_cast<SIZE_TYPE>(i_dimension);
                        }

                        Base::createArray(i_elementCount);
                        Base::setLength(i_elementCount);

                        m_shape.createArray(a_shape.length());
                        m_shape.setLength(a_shape.length());

                        m_strides.createArray(a_shape.length());
                        m_strides.setLength(a_shape.length());

                        for (SIZE_TYPE i = 0; i < a_shape.length(); ++i) {
                            m_shape.setFast(i, a_shape.getFast(i));
                        }

                        m_strides.setFast(a_shape.length() - 1, 1);
                        for (SIZE_TYPE i = a_shape.length() - 1; i > 0; --i) {
                            m_strides.setFast(i - 1, 
                                m_strides.getFast(i) * m_shape.getFast(i));
                        }
                        return true;
                    }

                    void clear() {
                        Base::clear();
                        m_shape.clear();
                        m_strides.clear();
                    }

                    const IndexArray& shape() const {
                        return m_shape;
                    }

                    const IndexArray& strides() const {
                        return m_strides;
                    }

                    bool set(const IndexArray& a_point, const VALUE_TYPE& a_value) {
                        SIZE_TYPE i_offset = 0;
                        if (!offset(a_point, i_offset)) {
                            return false;
                        }
                        Base::setFast(i_offset, a_value);
                        return true;
                    }

                    bool set(const IndexArray& a_point,
                             const IndexArray& a_extent,
                             const VALUE_TYPE& a_value) {
                        SIZE_TYPE i_elementCount = 0;
                        if (!region(a_point, a_extent, i_elementCount)
                            || Base::getArrayPointer() == nullptr) {
                            return false;
                        }
                        for (SIZE_TYPE i = 0; i < i_elementCount; ++i) {
                            SIZE_TYPE i_offset = 0;
                            if (!regionOffset(a_point, a_extent, i, i_offset)) {
                                return false;
                            }
                            Base::setFast(i_offset, a_value);
                        }
                        return true;
                    }

                    bool set(const IndexArray& a_point,
                             const IndexArray& a_extent,
                             const Base& a_values) {
                        SIZE_TYPE i_elementCount = 0;
                        if (!region(a_point, a_extent, i_elementCount)
                            || a_values.length() != i_elementCount
                            || Base::getArrayPointer() == nullptr) {
                            return false;
                        }
                        for (SIZE_TYPE i = 0; i < i_elementCount; ++i) {
                            SIZE_TYPE i_offset = 0;
                            if (!regionOffset(a_point, a_extent, i, i_offset)) {
                                return false;
                            }
                            Base::setFast(i_offset, a_values.getFast(i));
                        }
                        return true;
                    }

                    VALUE_TYPE getFast(const IndexArray& a_point) const {
                        SIZE_TYPE i_offset = 0;
                        for (SIZE_TYPE i = 0; i < m_shape.length(); ++i) {
                            i_offset += static_cast<SIZE_TYPE>(a_point.getFast(i))
                                      * static_cast<SIZE_TYPE>(m_strides.getFast(i));
                        }
                        return Base::getFast(i_offset);
                    }

                    bool get(const IndexArray& a_point, VALUE_TYPE& a_value) const {
                        SIZE_TYPE i_offset = 0;
                        if (!offset(a_point, i_offset)) {
                            return false;
                        }
                        a_value = Base::getFast(i_offset);
                        return true;
                    }

                    bool get(const IndexArray& a_point,
                             SIZE_TYPE a_length,
                             Base& a_out_array) const {
                        SIZE_TYPE i_offset = 0;
                        if (!offset(a_point, i_offset)
                            || a_length > static_cast<SIZE_TYPE>(Base::length()) - i_offset) {
                            return false;
                        }
                        a_out_array.createArray(a_length);
                        a_out_array.setLength(a_length);
                        for (SIZE_TYPE i = 0; i < a_length; ++i) {
                            a_out_array.setFast(i, Base::getFast(i_offset + i));
                        }
                        return true;
                    }

                    void getFast(const IndexArray& a_point,
                                 SIZE_TYPE a_length,
                                 Base& a_out_array) const {
                        SIZE_TYPE i_offset = 0;
                        for (SIZE_TYPE i = 0; i < m_shape.length(); ++i) {
                            i_offset += static_cast<SIZE_TYPE>(a_point.getFast(i))
                                      * static_cast<SIZE_TYPE>(m_strides.getFast(i));
                        }
                        a_out_array.createArray(a_length);
                        a_out_array.setLength(a_length);
                        for (SIZE_TYPE i = 0; i < a_length; ++i) {
                            a_out_array.setFast(i, Base::getFast(i_offset + i));
                        }
                    }

                    bool get(const IndexArray& a_point,
                             const IndexArray& a_extent,
                             DimensionalArray& a_out_array) const {
                        SIZE_TYPE i_element_count = 0;
                        if (!region(a_point, a_extent, i_element_count)
                            || !a_out_array.create(a_extent)) {
                            return false;
                        }
                        for (SIZE_TYPE i = 0; i < i_element_count; ++i) {
                            SIZE_TYPE i_offset = 0;
                            if (!regionOffset(a_point, a_extent, i, i_offset)) {
                                return false;
                            }
                            a_out_array.setFast(i, Base::getFast(i_offset));
                        }
                        return true;
                    }

                    void getFast(const IndexArray& a_point,
                                 const IndexArray& a_extent,
                                 DimensionalArray& a_out_array) const {
                        SIZE_TYPE i_element_count = 1;
                        for (SIZE_TYPE i = 0; i < a_extent.length(); ++i) {
                            i_element_count *= static_cast<SIZE_TYPE>(a_extent.getFast(i));
                        }
                        a_out_array.create(a_extent);
                        for (SIZE_TYPE i = 0; i < i_element_count; ++i) {
                            SIZE_TYPE i_offset = 0;
                            regionOffset(a_point, a_extent, i, i_offset);
                            a_out_array.setFast(i, Base::getFast(i_offset));
                        }
                    }

                private:
                    bool offset(const IndexArray& a_point, SIZE_TYPE& a_offset) const {
                        if (a_point.length() != m_shape.length()) {
                            return false;
                        }
                        a_offset = 0;
                        for (SIZE_TYPE i = 0; i < m_shape.length(); ++i) {
                            const INDEX_VALUE_TYPE i_coordinate = a_point.getFast(i);
                            if (i_coordinate < 0 || i_coordinate >= m_shape.getFast(i)) {
                                return false;
                            }
                            a_offset += static_cast<SIZE_TYPE>(i_coordinate)
                                      * static_cast<SIZE_TYPE>(m_strides.getFast(i));
                        }
                        return a_offset < static_cast<SIZE_TYPE>(Base::length());
                    }

                    bool region(const IndexArray& a_point,
                                const IndexArray& a_extent,
                                SIZE_TYPE& a_elementCount) const {
                        if (a_point.length() != m_shape.length()
                            || a_extent.length() != m_shape.length()
                            || m_shape.isEmpty()) {
                            return false;
                        }
                        a_elementCount = 1;
                        for (SIZE_TYPE i = 0; i < m_shape.length(); ++i) {
                            const INDEX_VALUE_TYPE i_coordinate = a_point.getFast(i);
                            const INDEX_VALUE_TYPE i_extent = a_extent.getFast(i);
                            if (i_coordinate < 0 || i_extent <= 0
                                || i_coordinate >= m_shape.getFast(i)
                                || i_extent > m_shape.getFast(i) - i_coordinate) {
                                return false;
                            }
                            a_elementCount *= static_cast<SIZE_TYPE>(i_extent);
                        }
                        return a_elementCount <= static_cast<SIZE_TYPE>(Base::length());
                    }

                    bool regionOffset(const IndexArray& a_point,
                                     const IndexArray& a_extent,
                                     SIZE_TYPE a_linearIndex,
                                     SIZE_TYPE& a_offset) const {
                        a_offset = 0;
                        for (SIZE_TYPE i = 0; i < m_shape.length(); ++i) {
                            SIZE_TYPE i_extentStride = 1;
                            for (SIZE_TYPE j = i + 1; j < m_shape.length(); ++j) {
                                i_extentStride *= static_cast<SIZE_TYPE>(a_extent.getFast(j));
                            }
                            const SIZE_TYPE i_localCoordinate =
                                (a_linearIndex / i_extentStride)
                                % static_cast<SIZE_TYPE>(a_extent.getFast(i));
                            a_offset += static_cast<SIZE_TYPE>(a_point.getFast(i))
                                      * static_cast<SIZE_TYPE>(m_strides.getFast(i));
                            a_offset += i_localCoordinate
                                      * static_cast<SIZE_TYPE>(m_strides.getFast(i));
                        }
                        return a_offset < static_cast<SIZE_TYPE>(Base::length());
                    }

                    IndexArray m_shape;
                    IndexArray m_strides;
            };

        }

    }

}