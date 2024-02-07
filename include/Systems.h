#pragma once

//===================================================
// Define Systems
//===================================================
class ModelSystem
{
private:
    /* data */
    entt::registry *m_registry;

public:
    // Public methods
    ModelSystem(entt::registry *reg)
    {
        HelloImGui::Log(HelloImGui::LogLevel::Info, "Created ModelSystem");
        m_registry = reg;
    }

    int is_image_loaded(ModelComponent *model, std::string file_name)
    {
        for (unsigned int i = 0; i < model->texture_list.size(); ++i)
            if (file_name.compare(model->texture_list[i].image_name) == 0)
                return model->texture_list[i].textureID;
        return -1;
    }

    unsigned int load_texture_image(std::string file_name, bool &load_complete)
    {
        // stbi_set_flip_vertically_on_load(1); // Call this function if the image is upside-down.
        std::size_t position = file_name.find_last_of("\\");
        file_name = "Images\\" + file_name.substr(position + 1);

        int width, height, num_components;
        unsigned char *image_data = stbi_load(file_name.c_str(), &width, &height, &num_components, 0);

        unsigned int textureID;
        glGenTextures(1, &textureID);

        if (image_data)
        {
            GLenum format{};

            if (num_components == 1)
                format = GL_RED;
            else if (num_components == 3)
                format = GL_RGB;
            else if (num_components == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, textureID);
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Recommended by NVIDIA Rep: https://devtalk.nvidia.com/default/topic/875205/opengl/how-does-gl_unpack_alignment-work-/

            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image_data);
            glGenerateMipmap(GL_TEXTURE_2D);

            // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexParameter.xhtml
            // ----------------------------------------------------------------------------------------------------------------
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); // GL_REPEAT... GL_MIRRORED_REPEAT... GL_CLAMP_TO_EDGE... GL_CLAMP_TO_BORDER.
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

            // float border_colour[] = {0.45, 0.55, 0.95};
            // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_colour); // For above when using: GL_CLAMP_TO_BORDER

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // GL_NEAREST... GL_LINEAR... GL_NEAREST_MIPMAP_NEAREST (See above link for full list)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // GL_NEAREST or GL_LINEAR.

            load_complete = true;
            stbi_image_free(image_data);

            HelloImGui::Log(HelloImGui::LogLevel::Debug, "Image loaded OK: %s", file_name.c_str());
        }
        else
        {
            load_complete = false;
            stbi_image_free(image_data);
            HelloImGui::Log(HelloImGui::LogLevel::Debug, "Image failed to load: %s", file_name.c_str());
        }
        return textureID;
    }

    void set_buffer_data(ModelComponent model, unsigned int index)
    {
        HelloImGui::Log(HelloImGui::LogLevel::Debug, "Num of meshes in mesh_list: %0d", model.mesh_list.size());
        
        if (index < model.mesh_list.size())
        {
//             ModelComponent::Mesh mesh = model->mesh_list[index];
            auto mesh = model.mesh_list[index];
            
            glGenVertexArrays(1, &mesh.vao);
            // glGenBuffers(1, mesh_list[index].vbo1);
            // glGenBuffers(1, mesh_list[index].vbo2);
            // glGenBuffers(1, mesh_list[index].vbo3);
            // glGenBuffers(1, mesh_list[index].ebo);
        }
        else
        {
            // Handle index out of bounds error or resize mesh_list if needed
        }
    }

    bool load_model(ModelComponent *model)
    {
        // model->scene = model->importer.ReadFile(model->filename, aiProcess_JoinIdenticalVertices | aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
        model->scene = model->importer.ReadFile(model->filename, aiProcess_JoinIdenticalVertices | aiProcess_Triangulate | aiProcess_FlipUVs);
        // model->scene = model->importer.ReadFile(model->filename, aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs);
        // model->scene = model->importer.ReadFile(model->filename, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!model->scene || !model->scene->mRootNode || model->scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE)
        {
            HelloImGui::Log(HelloImGui::LogLevel::Error, "Could not load model from path: %s", model->filename.c_str());
            HelloImGui::Log(HelloImGui::LogLevel::Error, "Importer error: %s", model->importer.GetErrorString());
            model->is_loaded = false;
            model->is_configured = false; // since loading failed, model is not configured
            return false;
        }
        else
        {
            auto const num_of_meshes = model->scene->mNumMeshes;
            model->num_meshes = num_of_meshes;
            model->mesh_list.resize(num_of_meshes);

            aiMesh *mesh{};
            int indices_offset = 0; // Not being used yet...

            // go through all the meshes in the scene
            for (unsigned int i = 0; i < num_of_meshes; ++i)
            {
                mesh = model->scene->mMeshes[i];

                aiMaterial *material = model->scene->mMaterials[mesh->mMaterialIndex]; // http://assimp.sourceforge.net/lib_html/structai_material.html
                auto num_of_textures = material->GetTextureCount(aiTextureType_DIFFUSE);

                HelloImGui::Log(HelloImGui::LogLevel::Debug, "Num of textures found: %0d", num_of_textures);

                // This loop will only run once (i.e. there's only 1 texture per mesh)
                for (unsigned int tex_count = 0; tex_count < num_of_textures; ++tex_count) // Also, only using: aiTextureType_DIFFUSE.
                {
                    aiString string;
                    material->GetTexture(aiTextureType_DIFFUSE, tex_count, &string); // Acquire the name of the image file to be loaded.

                    // Load mesh[i]'s texture if not already loaded
                    // ---------------------------------------------------------------
                    int already_loaded = is_image_loaded(model, string.C_Str()); // Returns -1 if texture Not already loaded, otherwise returns Existing texture handle.

                    if (already_loaded == -1) // Image not yet loaded so now attempt to load it.
                    {
                        bool load_success = false;
                        unsigned int texture_handle = load_texture_image(string.C_Str(), load_success);

                        if (load_success) // Although do nothing if the image fails to load.
                        {
                            ModelComponent::Texture texture;
                            texture.image_name = string.C_Str();
                            texture.textureID = texture_handle;

                            model->texture_list.push_back(texture);
                            model->mesh_list[i].tex_handle = texture_handle;
                        }
                    }
                    else
                    {
                        model->mesh_list[i].tex_handle = already_loaded;
                    }
                }

                // Loop through all mesh[i] vertices
                auto num_of_vertices = mesh->mNumVertices;
                auto has_normals = mesh->HasNormals();
                auto has_tex_coords = mesh->HasTextureCoords(0);

                HelloImGui::Log(HelloImGui::LogLevel::Debug, "Num of vertices: %0d", num_of_vertices);
                HelloImGui::Log(HelloImGui::LogLevel::Debug, "Has normals: %0d", has_normals);
                HelloImGui::Log(HelloImGui::LogLevel::Debug, "Has tex_coords: %0d", has_tex_coords);

                for (unsigned int i2 = 0; i2 < num_of_vertices; ++i2)
                {
                    glm::vec3 position{};
                    position.x = mesh->mVertices[i2].x;
                    position.y = mesh->mVertices[i2].y;
                    position.z = mesh->mVertices[i2].z;
                    model->mesh_list[i].vert_positions.push_back(position);

                    if (has_normals)
                    {
                        glm::vec3 normal{};
                        normal.x = mesh->mNormals[i2].x;
                        normal.y = mesh->mNormals[i2].y;
                        normal.z = mesh->mNormals[i2].z;
                        model->mesh_list[i].vert_normals.push_back(normal);
                    }
                    else
                    {
                        model->mesh_list[i].vert_normals.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
                    }

                    if (has_tex_coords)
                    {
                        glm::vec2 tex_coords{};
                        tex_coords.x = mesh->mTextureCoords[0][i2].x;
                        tex_coords.y = mesh->mTextureCoords[0][i2].y;
                        model->mesh_list[i].tex_coords.push_back(tex_coords);
                    }
                    else
                    {
                        model->mesh_list[i].tex_coords.push_back(glm::vec2(0.0f, 0.0f));
                    }
                }

                // Loop through all mesh indices
                auto num_of_mesh_faces = mesh->mNumFaces;

                for (unsigned int i3 = 0; i3 < num_of_mesh_faces; ++i3)
                {
                    for (unsigned int i4 = 0; i4 < mesh->mFaces[i3].mNumIndices; ++i4)
                    {
                        model->mesh_list[i].vert_indices.push_back(mesh->mFaces[i3].mIndices[i4] + indices_offset);
                    }
                }
                // indices_offset += mesh->mNumVertices;

//                set_buffer_data(model, i);
            }
            model->is_loaded = true;
            return true;
        }
    }

    void process()
    {
        auto view = m_registry->view<ModelComponent>();
        for (auto [entity, model] : view.each())
        {
            // Check if model is configured and not loaded
            if (model.is_configured && !model.is_loaded)
            {
                load_model(&model); // loading mesh succeeded
                // Show Model being loaded
                HelloImGui::Log(HelloImGui::LogLevel::Info, "model path: %s, configured: %0d, loaded: %0d", model.filename.c_str(), model.is_configured, model.is_loaded);
            }
        }
    }

    // Destructor
    ~ModelSystem() {}
};
