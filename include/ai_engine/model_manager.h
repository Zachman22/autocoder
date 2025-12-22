#ifndef AUTOCODER_MODEL_MANAGER_H
#define AUTOCODER_MODEL_MANAGER_H

#include <string>
#include <vector>
#include <map>
#include <memory>

namespace AutoCoder {
namespace AIEngine {

struct ModelInfo {
    std::string name;
    std::string version;
    std::string description;
    size_t parameter_count;
    std::vector<std::string> supported_languages;
    bool is_local;
    std::string path;
};

class ModelManager {
public:
    ModelManager();
    ~ModelManager();

    bool loadModel(const std::string& model_name);
    bool unloadModel(const std::string& model_name);

    bool downloadModel(const std::string& model_name, const std::string& destination);

    ModelInfo getModelInfo(const std::string& model_name) const;
    std::vector<ModelInfo> getAvailableModels() const;
    std::string getCurrentModel() const;

    bool switchModel(const std::string& model_name);

    bool isModelLoaded(const std::string& model_name) const;
    void setModelCachePath(const std::string& path);

private:
    void discoverLocalModels();
    void fetchRemoteModels();
    bool validateModel(const std::string& model_path);

    std::string current_model_;
    std::string cache_path_;
    std::map<std::string, ModelInfo> available_models_;
    std::map<std::string, void*> loaded_models_;
};

} // namespace AIEngine
} // namespace AutoCoder

#endif // AUTOCODER_MODEL_MANAGER_H
