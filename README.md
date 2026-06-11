# **NotinOOP - Fragrance Management & Recommendation System**

A C++ console application for managing user accounts, fragrance catalogs, transactions, and reviews. It is a **CLI emulation** of the website https://www.notino.bg

This project requires a C++17 compliant compiler and CMake version 3.15 or higher.

# **Key Logic & Algorithms**

### 1. Discount Generation
Discounts are generated randomly with a custom probability distribution using three distinct tiers:

* #### Default Discount (50% probability):
  Generates a simple discount between $5\%$ and $30\%$.

* #### Bonus Discount (30% probability):

  Generates a discount between $5\%$ and $20\%$ linked to a target transaction threshold (randomly selected between $10.00$ and $80.00$ EUR).

* #### Brand Discount (20% probability):

  Generates a high-value discount between $20\%$ and $60\%$, automatically tied to a randomly selected brand from the current catalog.

### 2. Fragrance Recommendation

The recommendation engine analyzes the user's wishlist to find products with overlapping ingredients.

1. **Frequency Analysis:** It scans the user's wishlist, counts how often ingredients appear, and identifies the user's **Top 3 favorite ingredients**.

2. **Tiered Matching:** The system scans the catalogue and builds a recommendation list using a 3-step fallback approach:

  * _Tier 1_: Finds fragrances containing **all 3** top ingredients.

  * _Tier 2_: Adds fragrances containing **at least 2** of the top ingredients.

  * _Tier 3_: Adds fragrances containing **at least 1** of the top ingredients.

3. **Filtration:** Items already present on the user's wishlist or already added to the recommendations list are automatically excluded.

# Project Structure

* `src/` — C++ source files (`.cpp`)

* `include/` — Header files (`.hpp`)

* `data/` — Plain text files acting as local databases (`users.txt`, `fragrances.txt`, etc.)
