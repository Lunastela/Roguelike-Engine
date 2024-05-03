#pragma once
#include <string>

namespace Roguelike {
    class Shader {
        public:
            Shader(const char* vertexPath, const char* fragmentPath);
            void Initialize();
            void Bind();

            // Shader Overloads
            // Uniform Float Overload
            void setUniform(const std::string &name, float value) const;
        private:
            unsigned int id;
    };
};