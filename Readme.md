# Bloom Filter – Experimental Implementation

## About This Project

This repository contains an implementation of the **Bloom Filter** algorithm created **solely for recreational programming purposes**.  
The main goal of this project is to explore probabilistic data structures, hashing techniques, and memory–performance trade-offs. It is **not intended for production use**.

## What Is a Bloom Filter?

A **Bloom Filter** is a **probabilistic data structure** used to test whether an element is **possibly a member** of a set or **definitely not a member**.

Key characteristics:

- Very **memory efficient**
- **Fast membership queries**
- **No false negatives**
- Possible **false positives**
- Does **not support element removal** in its classic form

In practice:
- If the Bloom Filter says *“no”*, the element is **definitely not present**
- If it says *“yes”*, the element **may or may not be present**

## How It Works (Overview)

- The Bloom Filter maintains a **bit array**
- It uses **multiple hash functions**
- To insert an element:
  - Each hash function maps the element to an index
  - The corresponding bits are set to `1`
- To query an element:
  - If all referenced bits are `1`, the element *may* exist
  - If any bit is `0`, the element definitely does not exist

## Real-World Use Cases

Although this implementation is experimental, Bloom Filters are widely used in real-world systems, including:

- **Databases** (to avoid unnecessary disk lookups)
- **Caches and CDNs**
- **Spam filtering**
- **Distributed systems**
- **Web browsers** (e.g., malicious URL checks)
- **Large-scale storage systems** such as Redis, Cassandra, and BigTable

## Educational Purpose

This project serves as:

- A hands-on exercise in data structures
- An introduction to probabilistic algorithms
- A way to study trade-offs between memory usage, accuracy, and performance

Feel free to experiment with different parameters and observe how they affect the false positive rate.

