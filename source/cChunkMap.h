#pragma once

class cEntity;
class cChunk;
class cChunkMap
{
public:
	cChunkMap( int a_Width, int a_Height );
	~cChunkMap();

	void AddChunk( cChunk* a_Chunk );
	unsigned int MakeHash( int a_X, int a_Z );

	cChunk* GetChunk( int a_X, int a_Y, int a_Z );
	void RemoveChunk( cChunk* a_Chunk );

	void Tick( float a_Dt );

	void UnloadUnusedChunks();
	bool RemoveEntityFromChunk( cEntity & a_Entity, cChunk* a_CalledFrom = 0 );
	void SaveAllChunks();
private:
	class cChunkData
	{
	public:
		cChunkData()
			: m_Compressed( 0 )
			, m_LiveChunk( 0 )
			, m_CompressedSize( 0 )
			, m_UncompressedSize( 0 )
		{}
		char* m_Compressed;
		unsigned int m_CompressedSize;
		unsigned int m_UncompressedSize;
		cChunk* m_LiveChunk;
	};

	class cChunkLayer
	{
	public:
		cChunkLayer()
			: m_Chunks( 0 )
			, m_X( 0 )
			, m_Z( 0 )
			, m_NumChunksLoaded( 0 )
		{}
		cChunkLayer( int a_NumChunks )
			: m_Chunks( new cChunkData[a_NumChunks] )
			, m_X( 0 )
			, m_Z( 0 )
			, m_NumChunksLoaded( 0 )
		{}
		cChunkData* GetChunk( int a_X, int a_Z );
		cChunkData* m_Chunks;
		int m_X, m_Z;
		int m_NumChunksLoaded;
	};

	void SaveLayer( cChunkLayer* a_Layer );
	cChunkLayer* LoadLayer( int a_LayerX, int a_LayerZ );
	cChunkLayer* GetLayerForChunk( int a_ChunkX, int a_ChunkZ );
	cChunkLayer* GetLayer( int a_LayerX, int a_LayerZ );
	cChunkLayer* AddLayer( const cChunkLayer & a_Layer );
	bool RemoveLayer( cChunkLayer* a_Layer );
	void CompressChunk( cChunkData* a_ChunkData );

	int m_NumLayers;
	cChunkLayer* m_Layers;

	class cChunkNode
	{
	public:
		cChunkNode();
		~cChunkNode();
		void push_back( cChunk* a_Chunk );
		unsigned int size() { return m_Size; }
		unsigned int allocated() { return m_Allocated; }
		void resize( unsigned int a_NewSize );

		void erase( cChunk* a_Chunk );

		cChunk** GetChunks() { return m_Chunks; }
	private:
		unsigned int m_Size;
		unsigned int m_Allocated;
		cChunk** m_Chunks;
	};

	cChunkNode* m_Nodes;
	int m_Width, m_Height;
};