#include <picobench/picobench.hpp>
#include <yama/matrix3x4.hpp>
#include <yama/matrix4x4.hpp>
#include <glm/mat4x4.hpp>

#include <cstdlib>

template <typename Y>
Y random_yama()
{
    Y y;
    for (size_t i = 0; i < Y::value_count; ++i)
    {
        y[i] = Y::value_type(rand()) / RAND_MAX;
    }
    return y;
}

template <typename YM>
void yama_matrix(picobench::state& s)
{
    std::vector<YM> mats;
    mats.reserve(s.iterations());
    for (int i = 0; i < s.iterations(); ++i)
    {
        mats.emplace_back(random_yama<YM>());
    }

    {
        picobench::scope _scope(s);
        for (auto& m : mats)
        {
            m.inverse();
        }
    }

    float sum = 0;
    for (const auto& m : mats)
    {
        sum += m(rand() % YM::rows_count, rand() % YM::columns_count);
    }
    
    s.set_result(picobench::result_t(sum));
}

void glm4x4(picobench::state& s)
{
    std::vector<glm::mat4> mats;
    mats.reserve(s.iterations());
    for (int i = 0; i < s.iterations(); ++i)
    {
        mats.emplace_back();
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                mats.back()[i][j] = float(rand()) / RAND_MAX;
            }
        }
    }

    {
        picobench::scope _scope(s);
        for (auto& m : mats)
        {
            m = glm::inverse(m);
        }
    }

    float sum = 0;
    for (const auto& m : mats)
    {
        sum += m[rand() % 4][rand() % 4];
    }

    s.set_result(picobench::result_t(sum));
}

PICOBENCH(glm4x4).label("glm");
PICOBENCH(yama_matrix<yama::matrix4x4>).label("y::4x4");
PICOBENCH(yama_matrix<yama::matrix3x4>).label("y::3x4");