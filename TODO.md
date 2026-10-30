# TODO

## World and chunks

- [ ] Move tile IDs and chunk dimensions to a shared map configuration.
- [ ] Add explicit map validation with clearer errors for invalid tile IDs.
- [ ] Merge adjacent water collision rectangles across tile rows where useful.
- [ ] Load and unload chunk data dynamically for very large worlds.
- [ ] Add a world entity/object layer for spawn points, items, and NPCs.
- [ ] Add automated tests for map loading, chunk activation, and collisions.

## Entities and gameplay systems

- [ ] Create a base `Entity` type with an ID, position, size, active state, and
  collision bounds.
- [ ] Add an entity manager responsible for creating, updating, drawing, and
  removing entities.
- [ ] Store static objects such as trees, buildings, and decorations in chunk
  files with local coordinates.
- [ ] Add an NPC system with names, dialogue, schedules, interaction ranges,
  and simple state-based behaviour.
- [ ] Add an enemy system with health, damage, detection range, target
  selection, and basic states such as idle, chase, attack, and dead.
- [ ] Add an animal system using the same movement and state patterns as NPCs
  while keeping animal-specific behaviour separate.
- [ ] Add an item definition database for shared data such as name, icon,
  stack size, value, and effects.
- [ ] Add world item entities for pickups, drops, containers, and respawnable
  resources.
- [ ] Add an inventory system for the player and other entities that can carry
  items.
- [ ] Add a common collision query in `World` for terrain and static objects,
  then add separate dynamic-entity collision checks.
- [ ] Activate, update, and unload entities together with their owning chunk.
- [ ] Add save/load support for entity state, inventories, defeated enemies,
  collected items, and opened containers.

### Suggested implementation order

1. Implement `Entity` and a small `EntityManager` without persistence.
2. Add static map objects and their collision rectangles to chunk files.
3. Add items and inventory before adding item pickups.
4. Add NPCs and dialogue using simple finite states.
5. Add enemies and animals by reusing movement, health, and collision helpers.
6. Add chunk-based activation and persistence after the basic gameplay works.

### Design suggestions

- Keep static geometry in `Chunk`/`World`; do not turn every tree or wall into
  a fully simulated entity.
- Keep NPCs, enemies, animals, and item pickups as dynamic entities managed by
  an entity system.
- Use composition where possible: movement, health, collision, inventory, and
  interaction should be reusable components rather than duplicated classes.
- Use stable entity IDs for save files and references instead of relying on
  vector indices.
- Keep item definitions separate from item instances: a definition describes
  an item type, while an instance stores quantity, durability, or owner data.
- Start with simple rectangle collisions and finite-state machines; optimise
  only after profiling shows a real bottleneck.
- Let chunk files contain spawn data and static objects, while runtime state is
  maintained by the world/entity manager and saved separately.

## Gameplay and UI

- [ ] Add configurable sprint multiplier and movement states.
- [ ] Replace placeholder minimap colors with configurable terrain styles.
- [ ] Add a proper camera/visibility system for inactive or distant chunks.
