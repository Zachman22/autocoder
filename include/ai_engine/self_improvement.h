#ifndef AUTOCODER_SELF_IMPROVEMENT_H
#define AUTOCODER_SELF_IMPROVEMENT_H

#include <string>
#include <vector>
#include <map>
#include <memory>

namespace AutoCoder {
namespace AIEngine {

struct ImprovementMetrics {
    double code_quality_score;
    double performance_score;
    double bug_reduction_rate;
    int successful_generations;
    int failed_generations;
    double average_response_time;
};

struct FeedbackData {
    std::string code;
    std::string prompt;
    bool was_successful;
    std::string error_message;
    double quality_rating;
    std::string improvement_notes;
};

class SelfImprovement {
public:
    SelfImprovement();
    ~SelfImprovement();

    void recordFeedback(const FeedbackData& feedback);
    void analyzeFeedback();

    std::string getImprovedPrompt(const std::string& original_prompt);
    std::vector<std::string> getSuggestedImprovements();

    void trainOnFeedback();
    void exportTrainingData(const std::string& filepath);
    bool importTrainingData(const std::string& filepath);

    ImprovementMetrics getMetrics() const;
    void resetMetrics();

    void enableContinuousLearning(bool enable);
    bool isContinuousLearningEnabled() const;

private:
    void updatePromptPatterns();
    void identifyCommonErrors();
    void optimizeGenerationParameters();

    std::vector<FeedbackData> feedback_history_;
    std::map<std::string, std::vector<std::string>> prompt_patterns_;
    std::map<std::string, int> error_patterns_;
    ImprovementMetrics metrics_;
    bool continuous_learning_enabled_;
};

} // namespace AIEngine
} // namespace AutoCoder

#endif // AUTOCODER_SELF_IMPROVEMENT_H
