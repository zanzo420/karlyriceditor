/**************************************************************************
 *  Karlyriceditor - a lyrics editor and CD+G / video export for Karaoke  *
 *  songs.                                                                *
 *  Copyright (C) 2009-2013 George Yunaev, support@ulduzsoft.com          *
 *                                                                        *
 *  This program is free software: you can redistribute it and/or modify  *
 *  it under the terms of the GNU General Public License as published by  *
 *  the Free Software Foundation, either version 3 of the License, or     *
 *  (at your option) any later version.                                   *
 *																	      *
 *  This program is distributed in the hope that it will be useful,       *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *  GNU General Public License for more details.                          *
 *                                                                        *
 *  You should have received a copy of the GNU General Public License     *
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 **************************************************************************/

#ifndef PROJECT_H
#define PROJECT_H

#include <QMap>
#include <QString>

class Editor;
class Lyrics;


class Project
{
	public:
		enum LyricType
		{
			LyricType_LRC1 = 1,
			LyricType_LRC2,
			LyricType_UStar, // if adding more, skip the #4!
		};

		enum Tag
		{
			Tag_Title = 1,
			Tag_Artist,
			Tag_Album,
			Tag_Language,
			Tag_Genre,
			Tag_MP3File,
			Tag_Cover,
			Tag_Background,
			Tag_Video,
			Tag_VideoGap,
			Tag_Edition,
			Tag_CreatedBy,
			Tag_Offset,
			Tag_Application,
			Tag_Appversion,
			Tag_CDG_bgcolor,
			Tag_CDG_infocolor,
			Tag_CDG_activecolor,
			Tag_CDG_inactivecolor,
			Tag_CDG_font,
			Tag_CDG_fontsize,
			Tag_CDG_titletime,
			Tag_CDG_preamble,

			Tag_Video_bgcolor,
			Tag_Video_infocolor,
			Tag_Video_activecolor,
			Tag_Video_inactivecolor,
			Tag_Video_font,
			Tag_Video_fontsize,
			Tag_Video_titletime,
			Tag_Video_preamble,
			Tag_Video_ImgSizeIndex,
			Tag_Video_FpsIndex,
			Tag_Video_EncodingIndex,
			Tag_Video_ContainerIndex,
			Tag_Video_AllKeyframes,
			Tag_Video_ExportNoAudio,
		};

		Project( Editor * editor );

		// load/save project from/to file
		bool	save( const QString& filename );
		bool	load( const QString& filename );

		// lyric type
		void	setType( LyricType type );
		LyricType	type() const;

		// Music file
		void	setMusicFile( const QString& musicfile );
		QString musicFile() const;

		// Set the music tag fields
		void	setTag( Tag tag, const QString& value );
		QString tag( Tag tagid, const QString& defvalue = QString::null ) const;

		// Is project modified?
		bool	isModified() const { return m_modified; }
		void	setModified();

		// Export lyrics as current format, and as any specific
		QByteArray	exportLyrics();
		QByteArray	exportLyricsAsLRC1();
		QByteArray	exportLyricsAsLRC2();
		QByteArray	exportLyricsAsUStar();

		// Import lyrics. So far the formats are fairly recognizable, so other imports are private
		bool	importLyrics( const QString& filename );

		// Convert the autogenerated LRC lyrics into the project
		bool	convertLyrics( const QString& content );

		// Clear the project
		void	clear();

		// Set/access the song length
		void	setSongLength( qint64 length );
		qint64	getSongLength() const;

		// Split the time mark
		static void splitTimeMark( qint64 mark, int * min, int * sec, int * msec );

	private:
		bool	importLyricsLRC( const QStringList & readlyrics, Lyrics& lyrics, bool relaxed = false );
		bool	importLyricsUStar( const QStringList & readlyrics, Lyrics& lyrics );

		void	appendIfPresent( int id, const QString& prefix, QString& src, LyricType type );
		QString	generateLRCheader();
		QString	generateUStarheader();
		void	update( int id, const QString& value );

		int		tagToId( Tag tagid ) const;
		bool	m_modified;
		Editor* m_editor;
		qint64	m_totalSongLength;

		// This container stores all project-related data
		QMap< int, QString>	m_projectData;

};

#endif // PROJECT_H
