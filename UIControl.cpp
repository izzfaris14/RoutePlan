void UIControl::displayMatches(const SchedRepo& repo) {
	std::cout << "\n=== GENERATED ROUTES ===\n" << std::endl;

	const auto& routes = repo.getRoutes();

	if (routes.empty()) {
		std::cout << "No matches found." << std::endl;
	}
	else {
		for (const auto& r : routes) {
			std::cout << "-----------------------------------" << std::endl;
			std::cout << r.getRouteString() << std::endl;
		}
	}
	std::cout << "===================================\n" << std::endl;
}