#pragma once

#include <deque>
#include <iostream>
#include <string>
#include <vector>

#include "search_server.h"
#include "document.h"

class RequestQueue {
public:
    explicit RequestQueue(const SearchServer& search_server) : search_server_(search_server) {
        // напишите реализацию
    }
    // сделаем "обёртки" для всех методов поиска, чтобы сохранять результаты для нашей статистики
    template <typename DocumentPredicate>
    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentPredicate document_predicate) {
        // напишите реализацию
        std::vector<Document> documents = search_server_.FindTopDocuments(raw_query, document_predicate);
        AddRequest(documents);
        return documents;
    }

    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentStatus status);

    std::vector<Document> AddFindRequest(const std::string& raw_query);

    int GetNoResultRequests() const;
private:
    struct QueryResult {
        // определите, что должно быть в структуре
        std::vector<Document> documnets;
        bool success = false;

    };
    void AddRequest(const std::vector<Document>& documents);

    std::deque<QueryResult> requests_;
    const static int min_in_day_ = 1440;
    const SearchServer& search_server_;
    int no_result_request_count = 0;
    int min_count_ = 0;

};


















