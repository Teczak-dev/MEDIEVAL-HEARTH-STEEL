# Map and chunk format

The map is stored in [`assets/maps/map.json`](../assets/maps/map.json).
The game loads the map as a rectangular two-dimensional array of chunks.

## Chunk dimensions

Each chunk contains **128 columns × 128 rows** of tiles. A tile is **64 × 64
pixels**, so one chunk covers **8192 × 8192 pixels** in the game world.

These values are defined as defaults in `World` and apply to every chunk in
the JSON map. Keep every chunk the same size so that world positions and
collision boundaries remain consistent.

### Why 128 × 128?

`128 × 128` is the current compromise between streaming overhead and the
amount of data processed at once. A `256 × 256` or `512 × 512` chunk would
contain four or sixteen times as many tiles, respectively, making rendering
and collision checks more expensive when nearby chunks are active. Smaller
chunks can be considered later if the map needs more precise streaming or if
profiling shows that active chunks contain too many tiles.

## JSON structure

The map file contains only the `chunks` field:

```json
{
  "chunks": [
    [
      { "fill": 1 },
      { "fill": 1 }
    ],
    [
      { "fill": 1 },
      { "fill": 3 }
    ]
  ]
}
```

`chunks[y][x]` identifies the chunk at horizontal position `x` and vertical
position `y`. A chunk can use either:

- `fill` — fills the whole chunk with one tile ID;
- `tiles` — provides a complete 128-row × 128-column tile matrix.

An empty or unknown chunk shape is not recommended; use `fill` for simple
areas and `tiles` when a chunk needs a custom shape.

## Tile IDs and collisions

The current tileset uses these IDs:

| ID | Meaning |
|---:|---|
| 1 | grass |
| 2 | dirt |
| 3 | water |

Water is the only tile that currently creates collision. The loader scans every
water tile and generates one-tile-high collision rectangles for contiguous
water segments. Collision rectangles are therefore **not written manually** in
the JSON file. To make a lake or river, place adjacent chunks or tile rows
with `fill: 3` or custom `tiles` data.

Chunks around the player are activated at runtime. This keeps rendering and
collision checks limited to the nearby part of the map while preserving the
same world coordinates.

## Code responsibilities

The world code is split into three small layers:

- `Chunk` (`include/Worlds/Chunk.hpp`, `src/Worlds/Chunk.cpp`) represents one
  `128 × 128` tile area. It stores tile IDs, generated water collision
  rectangles, and whether the chunk is active.
- `World` (`include/Worlds/World.hpp`, `src/Worlds/World.cpp`) owns the 2D
  collection of chunks. It loads `map.json`, validates chunk dimensions,
  activates nearby chunks, checks collisions, and calculates world size.
- `Map` (`include/Worlds/Map.hpp`, `src/Worlds/Map.cpp`) is the gameplay-facing
  facade. `Game`, `Player`, and the UI use `Map`; internally it delegates
  world and chunk work to `World` and handles the tileset texture.

To use the map in gameplay, construct `Map` with the JSON path, call
`UpdateActiveChunks(playerPosition)` before movement, then use `Collides`,
`ClampPosition`, `Draw`, or `DrawMinimap`. Code that needs to work with the
whole world should normally use `Map`, not access chunks directly.
