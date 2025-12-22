#ifndef AUTOCODER_INFERENCE_ENGINE_H
#define AUTOCODER_INFERENCE_ENGINE_H

#include <string>
#include <vector>
#include <memory>

namespace AutoCoder {
namespace AIEngine {

struct InferenceConfig {
    float temperature;
    int max_tokens;
    float top_p;
    float top_k;
    int num_return_sequences;
    bool use_cache;
};

struct InferenceResult {
    std::vector<std::string> generated_texts;
    std::vector<float> scores;
    int tokens_generated;
    double inference_time_ms;
    bool success;
    std::string error_message;
};

class InferenceEngine {
public:
    InferenceEngine();
    ~InferenceEngine();

    bool initialize(const std::string& model_path);
    void shutdown();

    InferenceResult generate(
        const std::string& prompt,
        const InferenceConfig& config
    );

    InferenceResult generateWithContext(
        const std::string& prompt,
        const std::vector<std::string>& context,
        const InferenceConfig& config
    );

    void setConfig(const InferenceConfig& config);
    InferenceConfig getConfig() const;

    bool warmup();
    void clearCache();

private:
    std::string preprocessPrompt(const std::string& prompt);
    std::string postprocessOutput(const std::string& output);

    void* model_handle_;
    InferenceConfig config_;
    bool initialized_;
    std::string model_path_;
};

} // namespace AIEngine
} // namespace AutoCoder

#endif // AUTOCODER_INFERENCE_ENGINE_H
