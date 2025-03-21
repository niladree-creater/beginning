from flask import Flask, request, jsonify
from elasticsearch import Elasticsearch

app = Flask(__name__)
es = Elasticsearch(["http://localhost:9200"])  # Ensure Elasticsearch is running

# Index sample medical data (for demonstration)
def index_data():
    medical_data = [
        {"id": 1, "title": "Diabetes Treatment", "content": "Insulin and dietary changes can help manage diabetes."},
        {"id": 2, "title": "Heart Disease Symptoms", "content": "Chest pain, shortness of breath, and fatigue are common symptoms."},
        {"id": 3, "title": "COVID-19 Prevention", "content": "Wearing masks, vaccination, and social distancing can prevent COVID-19."}
    ]
    
    for doc in medical_data:
        es.index(index="healthcare", id=doc["id"], body=doc)

@app.route("/search", methods=["GET"])
def search():
    query = request.args.get("q")
    
    if not query:
        return jsonify({"error": "Query parameter 'q' is required"}), 400
    
    body = {
        "query": {
            "multi_match": {
                "query": query,
                "fields": ["title", "content"]
            }
        }
    }
    
    res = es.search(index="healthcare", body=body)
    
    results = [{"title": hit["_source"]["title"], "content": hit["_source"]["content"]} for hit in res["hits"]["hits"]]
    
    return jsonify(results)

if __name__ == "__main__":
    index_data()  # Run once to index initial data
    app.run(debug=True)