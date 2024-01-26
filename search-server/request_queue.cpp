//Вставьте сюда своё решение из урока «Очередь запросов» темы «Стек, очередь, дек».‎
#include "request_queue.h"

using namespace std;

std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query, DocumentStatus status) {
    // напишите реализацию
    vector<Document> documents = search_server_.FindTopDocuments(raw_query, status);
    AddRequest(documents);
    return documents;
}

vector<Document> RequestQueue::AddFindRequest(const string& raw_query) {
    // напишите реализацию
    vector<Document> documents = search_server_.FindTopDocuments(raw_query);
    AddRequest(documents);
    return documents;
}

int RequestQueue::GetNoResultRequests() const {
    // напишите реализацию
    return no_result_request_count;
}

void RequestQueue::AddRequest(const std::vector<Document>& documents) {
    if (min_count_ == min_in_day_) {
        if (!requests_.front().success) {
            no_result_request_count--;
        }
        requests_.pop_front();
        min_count_--;
    }
    min_count_++;
    if (documents.empty()) no_result_request_count++;
    requests_.push_back({ documents, !documents.empty() });
}
