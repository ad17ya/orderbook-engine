# High-Performance Order Book & Matching Engine (C++)

A deterministic, in-memory limit order book and matching engine implementing **strict price-time priority**.  
Designed to resemble real **trading-infrastructure cores**, not application-level systems.

---

## What This Is

- In-memory **limit order book**
- **Immediate matching** on order entry
- **Price-time priority** enforced by data structures
- Single-threaded, deterministic core
- Debug visualization of full book state

---

## Why This Project

This project demonstrates **systems-level thinking** required for high-performance trading infrastructure:

- Correctness by construction  
- Deterministic behavior (same input → same output)  
- Explicit ownership & lifecycle  
- Hot-path discipline (no locks, no heap allocation, no I/O)

---

## Key Design Choices

- **Integer price ticks (`int64_t`)**
  - No floating point in the engine
  - Exact comparisons, deterministic ordering

- **Intrusive FIFO queues per price**
  - Enforces time priority structurally
  - O(1) insert and remove

- **Ordered price levels**
  - Bids: highest price first
  - Asks: lowest price first

- **No ownership in the engine**
  - Orders are linked/unlinked only
  - No `new`, no `delete`, no smart pointers

---

## Matching Behavior

1. Incoming orders are matched immediately
2. Always match against the **best opposing price**
3. FIFO within the same price level
4. Partial fills supported
5. Remaining quantity rests in the book

**Trade price = resting order’s price**

---

## Demonstrating Correctness

- Deterministic trade log (replayable)
- Designed scenarios proving:
  - Price priority
  - FIFO time priority
  - Partial fills
- Side-by-side BID / ASK book visualization for inspection

---

## What This Project Avoids (Intentionally)

- ❌ UI
- ❌ Database
- ❌ Threading
- ❌ Floating-point arithmetic
- ❌ Over-engineering

Focus is on **high-performance core logic and correctness**, not features.

---

## Build & Run

```bash
make
./engine
