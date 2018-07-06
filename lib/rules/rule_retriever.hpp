std::ifstream readConfigFile();
nlohmann::json convertFileToJSON(std::ifstream f);
int getBulletPointsCount(nlohmann::json rulesJSON);
int getBulletPointsMaxLength(nlohmann::json rulesJSON);
int getBulletPointsMinLength(nlohmann::json rulesJSON);
int getDescriptionMaxLength(nlohmann::json rulesJSON);
int getDescriptionMinLength(nlohmann::json rulesJSON);
int getSummaryMaxLength(nlohmann::json rulesJSON);
int getSummaryMinLength(nlohmann::json rulesJSON);
bool hasRuleErrorThrown(nlohmann::json rulesJSON);
bool identifyTypos(nlohmann::json rulesJSON);
bool requiresBulletPoints(nlohmann::json rulesJSON);
bool requiresDescription(nlohmann::json rulesJSON);
bool requiresDocFormat(nlohmann::json rulesJSON);
bool requiresNitFormat(nlohmann::json rulesJSON);
bool requiresSummaryCapital(nlohmann::json rulesJSON);
bool requiresWIPFormat(nlohmann::json rulesJSON);
