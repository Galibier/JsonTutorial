#pragma once

#include <iosfwd>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace json {

	class JsonValue;

	enum class JsonType {
		kNull,
		kBool,
		kNumber,
		kString,
		kArray,
		kObject
	};

	class Json final {
	public:
		using array_t = std::vector<Json>;
		using object_t = std::unordered_map<std::string, Json>;

		static Json parse(const std::string& content, std::string& errMsg) noexcept;

		std::string serialize() const noexcept;

		explicit Json(const char* cstr) :Json(std::string(cstr)) {}
		explicit Json(const std::string&);
		explicit Json(const array_t&);
		explicit Json(const object_t&);

		Json(const Json&);
		Json(Json&&) noexcept;
		~Json();
		Json& operator=(Json);

		JsonType type() const noexcept;
		bool isNull() const noexcept;
		bool isBool() const noexcept;
		bool isNumber() const noexcept;
		bool isString() const noexcept;
		bool isArray() const noexcept;
		bool isObject() const noexcept;

		bool toBool() const;
		double toDouble() const;
		const std::string& toString() const;
		const array_t& toArray() const;
		const object_t& toObject() const;

		Json& operator[](std::size_t);
		const Json& operator[](std::size_t) const;
		Json& operator[](const std::string&);
		const Json& operator[](const std::string&) const;

		std::size_t size() const noexcept;

	private:
		void swap(Json&) noexcept;
		std::string serializeString() const noexcept;
		std::string serializeArray() const noexcept;
		std::string serializeObject() const noexcept;

		std::unique_ptr<JsonValue> value_;
	};

	inline std::ostream& operator<<(std::ostream &os, const Json& json) {
		return os << json.serialize();
	}

	bool operator==(const Json&, const Json&) noexcept;
	inline bool operator!=(const Json& lhs, const Json& rhs) noexcept {
		return !(lhs == rhs);
	}
}